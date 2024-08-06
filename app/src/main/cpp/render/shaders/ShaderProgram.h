//
// Created by VeraTag on 03.08.2024.
//

#ifndef CUBE_SHADERPROGRAM_H
#define CUBE_SHADERPROGRAM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <functional>
#include <exception>

#include "glm/glm.hpp"
#include <GLES3/gl3.h>

#include "Shader.h"

namespace Render::Shaders {
    class ShaderProgram {
    public:
        using Ptr = std::shared_ptr<ShaderProgram>;

        // Конструктор считывает данные и выполняет построение шейдера
        //ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
        ShaderProgram(const char* vertexSource, const char* fragmentSource);
        ~ShaderProgram();

        // Использование/активация шейдера
        void use();

        // Полезные uniform-функции
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void set3UnsignedIntVector(const std::string& name, void* uiv) const;
        void set3FloatVector(const std::string& name, float c1, float c2, float c3) const;
        void set3FloatVector(const std::string& name, const glm::vec3& vector) const;
        void set4FloatVector(const std::string& name, float c1, float c2, float c3, float c4) const;
        void set4FloatVector(const std::string& name, const glm::vec4& vector) const;
        void set4FloatMat(const std::string& name, const GLfloat* value) const;

        [[nodiscard]] unsigned int getId() const;

    private:
        unsigned int _id; // IdCounter - идентификатор программы
    };

} // Render

#endif //CUBE_SHADERPROGRAM_H
