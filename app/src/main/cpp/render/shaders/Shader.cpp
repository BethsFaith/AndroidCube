//
// Created by VeraTag on 06.08.2024.
//

#include "Shader.h"

namespace Render::Shaders {
    Shader::Shader(GLenum type) {
        _id = glCreateShader(type);
    }

    Shader::~Shader() {
        glDeleteShader(_id);
    }

    bool Shader::compileFromFile(const std::string& path) {
        std::string vertexCode;
        std::ifstream vShaderFile;

        // Убеждаемся, что объекты ifstream могут выбросить исключение
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            // Открываем файлы
            vShaderFile.open(path);
            std::stringstream vShaderStream;

            // Считываем содержимое файловых буферов в потоки
            vShaderStream << vShaderFile.rdbuf();

            // Закрываем файлы
            vShaderFile.close();

            // Конвертируем данные из потока в строковые переменные
            vertexCode = vShaderStream.str();
        } catch (std::ifstream::failure& e) {
            _error = "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n";

            return false;
        }

        return compileFromString(vertexCode.c_str());
    }

    bool Shader::compileFromString(const char *source) {
        // Этап №2: Компилируем шейдеры
        int success;
        char infoLog[512];

        // Вершинный шейдер
        glShaderSource(_id, 1, &source, NULL);
        glCompileShader(_id);

        // Если есть ошибки компиляции, то выводим информацию о них
        glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(_id, 512, NULL, infoLog);

            _error = "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
            _error += infoLog;
        }

        return success;
    }

    GLuint Shader::getId() const {
        return _id;
    }

    std::string Shader::getError() {
        return _error;
    }
} // Render