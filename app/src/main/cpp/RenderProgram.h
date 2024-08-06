//
// Created by VeraTag on 03.08.2024.
//

#ifndef CUBE_RENDERPROGRAM_H
#define CUBE_RENDERPROGRAM_H

#include <iostream>

#include "shaders/ShaderProgram.h"
#include "render/Object.h"
#include "render/primitives/PCube.h"
#include "render/techniques/Transform3dTechnique.h"

class RenderProgram {
public:
    RenderProgram(const RenderProgram &) = delete;
    RenderProgram& operator=(const RenderProgram &) = delete;

    static RenderProgram& instance();

    void setupGraphic(GLint width, GLint height);

    bool compileShaderProgram(const std::string& vertSource, const std::string& fragShader);

    void renderFrame();

    std::string getLastError();

protected:
    void clearColor() const;

private:
    RenderProgram() = default;

    glm::vec4 _clearColor{1.0,1.0,1.0,1.0};

    Render::Object::Ptr _object;
    Render::Shaders::ShaderProgram::Ptr _shaderProgram;

    std::string _lastError;
};

#endif //CUBE_RENDERPROGRAM_H
