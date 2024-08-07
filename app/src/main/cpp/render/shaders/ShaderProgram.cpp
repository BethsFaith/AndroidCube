//
// Created by VeraTag on 03.08.2024.
//

#include "ShaderProgram.h"

namespace Render::Shaders {
    ShaderProgram::ShaderProgram() {
        // Шейдерная программа
        _id = glCreateProgram();
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(_id);
    }

    bool ShaderProgram::compileAndLink(const char *vertexSource, const char *fragmentSource) {
        Shader vertex(GL_VERTEX_SHADER);
        Shader fragment(GL_FRAGMENT_SHADER);

        auto res = vertex.compileFromString(vertexSource);
        if (!res) {
            _error = vertex.getError();
            return res;
        }
        res = fragment.compileFromString(fragmentSource);
        if (!res) {
            _error = fragment.getError();
            return res;
        }

        glAttachShader(_id, vertex.getId());
        glAttachShader(_id, fragment.getId());
        glLinkProgram(_id);

        return res;
    }

    void ShaderProgram::use() {
        glUseProgram(_id);
    }

    void ShaderProgram::setBool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
    }

    void ShaderProgram::setInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
    }

    void ShaderProgram::setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
    }

    void ShaderProgram::set3FloatVector(const std::string& name, float c1, float c2, float c3) const {
        glUniform3f(glGetUniformLocation(_id, name.c_str()), c1, c2, c3);
    }

    void ShaderProgram::set3FloatVector(const std::string& name, const glm::vec3& vector) const {
        glUniform3f(glGetUniformLocation(_id, name.c_str()), vector.x, vector.y, vector.z);
    }

    void ShaderProgram::set3UnsignedIntVector(const std::string& name, void* uiv) const {
        glUniform3uiv(glGetUniformLocation(_id, name.c_str()), 1, (GLuint*)&uiv);
    }

    void ShaderProgram::set4FloatVector(const std::string& name, float c1, float c2, float c3, float c4) const {
        glUniform4f(glGetUniformLocation(_id, name.c_str()), c1, c2, c3, c4);
    }

    void ShaderProgram::set4FloatVector(const std::string& name, const glm::vec4& vector) const {
        glUniform4f(glGetUniformLocation(_id, name.c_str()), vector.x, vector.y, vector.z, vector.w);
    }

    void ShaderProgram::set4FloatMat(const std::string& name, const GLfloat* value) const {
        glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, value);
    }

    unsigned int ShaderProgram::getId() const {
        return _id;
    }

    std::string ShaderProgram::getError() {
        return _error;
    }
} // Render