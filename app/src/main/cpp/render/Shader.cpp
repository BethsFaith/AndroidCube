//
// Created by VeraTag on 03.08.2024.
//

#include "Shader.h"

namespace Render {
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
        // Этап №1: Получение исходного кода вершинного/фрагментного шейдера из переменной filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        // Убеждаемся, что объекты ifstream могут выбросить исключение
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            // Открываем файлы
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            // Считываем содержимое файловых буферов в потоки
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // Закрываем файлы
            vShaderFile.close();
            fShaderFile.close();

            // Конвертируем данные из потока в строковые переменные
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (std::ifstream::failure& e) {
            throw std::runtime_error("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // Этап №2: Компилируем шейдеры
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        // Вершинный шейдер
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);

        // Если есть ошибки компиляции, то выводим информацию о них
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);

            char errorInfo[] = "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
            strcat(errorInfo, infoLog);

            glDeleteShader(vertex);

            throw std::runtime_error(errorInfo);
        }

        // фрагментный шейдер
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);

            char errorInfo[] = "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
            strcat(errorInfo, infoLog);

            glDeleteShader(vertex);
            glDeleteShader(fragment);

            throw std::runtime_error(errorInfo);
        }

        // Шейдерная программа
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        // Если есть ошибки связывания, то выводим информацию о них
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);

            char errorInfo[] = "ERROR::SHADER::PROGRAM::LINKING_FAILED\n";
            strcat(errorInfo, infoLog);

            glDeleteShader(vertex);
            glDeleteShader(fragment);

            throw std::runtime_error(errorInfo);
        }

        // После того, как мы связали шейдеры с нашей программой, удаляем их, так как они нам больше не нужны
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Shader::use() {
        glUseProgram(ID);
    }

    void Shader::setBool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::set3FloatVector(const std::string& name, float c1, float c2, float c3) const {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), c1, c2, c3);
    }

    void Shader::set3FloatVector(const std::string& name, const glm::vec3& vector) const {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), vector.x, vector.y, vector.z);
    }

    void Shader::set3UnsignedIntVector(const std::string& name, void* uiv) const {
        glUniform3uiv(glGetUniformLocation(ID, name.c_str()), 1, (GLuint*)&uiv);
    }

    void Shader::set4FloatVector(const std::string& name, float c1, float c2, float c3, float c4) const {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), c1, c2, c3, c4);
    }

    void Shader::set4FloatVector(const std::string& name, const glm::vec4& vector) const {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), vector.x, vector.y, vector.z, vector.w);
    }

    void Shader::set4FloatMat(const std::string& name, const GLfloat* value) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value);
    }

    unsigned int Shader::getId() const {
        return ID;
    }
} // Render