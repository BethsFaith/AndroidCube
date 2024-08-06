//
// Created by VeraTag on 03.08.2024.
//

#include "RenderProgram.h"

RenderProgram &RenderProgram::instance() {
    static RenderProgram instance_;

    return instance_;
}

void RenderProgram::setupGraphic(unsigned int width, unsigned int height) {
    auto cube = std::make_shared<Render::Primitives::PCube>(
            Render::Primitives::Settings{ .withNormals = true,
                                                  .withTextureCoords = false,
                                                  .withTangent = false,
                                                  .withBitangent = false });
    cube->bindData(GL_STATIC_DRAW);

    auto transformTechnique = std::make_shared<Render::Techniques::Transform3dTechnique>();
    transformTechnique->setModel(50.0f, glm::vec3(0.5f, 1.0f, 0.0f));
    transformTechnique->setView(glm::vec3(0.0f, 0.0f, -10.0f));
    transformTechnique->setProjection(45.0f, width, height, 0.1f, 100.0f);

    _object = std::make_shared<Render::Object>();
    _object->setPrimitive(cube);
    _object->addTechnique(Render::Techniques::TRANSFORM, transformTechnique);
    _object->enableTechnique(Render::Techniques::TRANSFORM);

    glViewport(0, 0, (GLint)width, (GLint)height);
}

void RenderProgram::compileShaderProgram(const std::string& vertSource, const std::string& fragShader) {
    _shaderProgram = std::make_shared<Render::Shaders::ShaderProgram>(
            vertSource.c_str(),
            fragShader.c_str());
}

void RenderProgram::renderFrame() {
    clearColor();

    if (_object != nullptr && _shaderProgram != nullptr) {
        _object->render(_shaderProgram);
    }
}

void RenderProgram::clearColor() const {
    glClearColor(_clearColor.x, _clearColor.y, _clearColor.z, _clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
