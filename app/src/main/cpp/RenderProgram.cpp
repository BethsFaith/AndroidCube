//
// Created by VeraTag on 03.08.2024.
//

#include "RenderProgram.h"

RenderProgram::RenderProgram() {
}

RenderProgram &RenderProgram::instance() {
    static RenderProgram instance_;

    return instance_;
}

void RenderProgram::setupGraphic(GLint width, GLint height) {
    auto cube = std::make_shared<Render::Primitives::PCube>(
            Render::Primitives::Settings{ .withNormals = true,
                    .withTextureCoords = false,
                    .withTangent = false,
                    .withBitangent = false });
    cube->bindData(GL_STATIC_DRAW);

    _object = std::make_shared<Render::Object>();
    _object->setPrimitive(cube);

    transformTechnique = std::make_shared<Render::Techniques::Transform3dTechnique>();
    transformTechnique->setModel(glm::vec3{0.0f});
//    transformTechnique->setModel(glm::vec3{0.0f}, Render::Techniques::Transform3dTechnique::Rotate{
//                                                    .angle = 0.0f,
//                                                    .axis = glm::vec3(0.0f, 1.0f, 0.0f)});
    transformTechnique->setView(glm::vec3(0.0f, 0.0f, -20.0f));
    transformTechnique->setProjection(45.0f, width, height, 0.1f, 100.0f);

    _object->addTechnique(Render::Techniques::TRANSFORM, transformTechnique);
    _object->enableTechnique(Render::Techniques::TRANSFORM);

    glViewport(0, 0, width, height);
}

bool RenderProgram::compileShaderProgram(const std::string& vertSource, const std::string& fragShader) {
    _shaderProgram = std::make_shared<Render::Shaders::ShaderProgram>();

    auto res = _shaderProgram->compileAndLink(vertSource.c_str(),
                                              fragShader.c_str());
    if (!res) {
        _lastError = _shaderProgram->getError();
    }
    return res;
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

std::string RenderProgram::getLastError() {
    return _lastError;
}

void RenderProgram::rotateCube(glm::vec3 axis) {
    static auto pos = glm::vec3{0.0f, 0.0f, 0.0f};
    static auto angle = 0.0f;
    static float const speed = 1.0f;

    if (axis.y > 0.0) {
        angle += speed;
    } else {
        angle -= speed;
        axis.y = 1.0f;
    }
    transformTechnique->setRotate(Render::Techniques::Transform3dTechnique::Rotate{
            .angle = angle,
            .axis = axis});
    transformTechnique->calculateModel();
}

void RenderProgram::orbitCube(bool forward) {
    static auto start = glm::vec3{0.0f, 0.0f, 0.0f};
    static auto angle = 0.0f;
    static const auto r = 5.0f;
    static float const speed = 0.15f;
    if (_object != nullptr && _shaderProgram != nullptr) {
        if (forward) {
            angle += speed;
        } else {
            angle -= speed;
        }

        auto pos = start;
        pos.x = r * std::cos(angle + start.x);
        pos.y = r * std::sin(angle + start.y);

        transformTechnique->setTransform(pos);
        transformTechnique->calculateModel();
    }
}
