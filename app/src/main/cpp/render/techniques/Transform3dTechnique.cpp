//
// Created by VeraTag on 06.08.2024.
//

#include "Transform3dTechnique.h"

namespace Render::Techniques {

    void Transform3dTechnique::execute(Shaders::ShaderProgram::Ptr shader) {
        shader->set4FloatMat("model", glm::value_ptr(_model));
        shader->set4FloatMat("view", glm::value_ptr(_view));
        shader->set4FloatMat("projection", glm::value_ptr(_projection));
    }

    void Transform3dTechnique::setModel(glm::mat4 model) {
        _model = model;
    }

    void Transform3dTechnique::setModel(float angleDegrees, glm::vec3 pos) {
        _model = glm::mat4(1.0f);
        _model = glm::rotate(_model, glm::radians(angleDegrees), pos);
    }

    void Transform3dTechnique::setView(glm::mat4 view) {
        _view = view;
    }

    void Transform3dTechnique::setView(glm::vec3 pos) {
        _view = glm::mat4(1.0f);
        _view = glm::translate(_view, pos);
    }

    void Transform3dTechnique::setProjection(glm::mat4 projection) {
        _projection = projection;
    }

    void Transform3dTechnique::setProjection(float angleDegrees, float screenWidth, float screenHeight,
                                             float zNear, float zFar) {
        _projection = glm::perspective(glm::radians(45.0f),
                                       screenWidth / screenHeight, zNear, zFar);
    }
}