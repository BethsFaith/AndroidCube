//
// Created by VeraTag on 06.08.2024.
//

#ifndef CUBE_SHADER_H
#define CUBE_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <GLES3/gl3.h>

namespace Render::Shaders {
    class Shader {
    public:
        using Ptr = std::shared_ptr<Shader>;

        explicit Shader(GLenum type);
        ~Shader();

        bool compileFromFile(const std::string& path);
        bool compileFromString(const char* source);

        [[nodiscard]] GLuint getId() const;
        std::string getError();
    private:
        GLuint _id;

        std::string _error;
    };

} // Render

#endif //CUBE_SHADER_H
