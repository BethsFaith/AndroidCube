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

    void Transform3dTechnique::setModel(glm::vec3 pos) {
        _model = glm::mat4(1.0f);
        _model = glm::translate(_model, pos);
    }

    void Transform3dTechnique::setModel(glm::vec3 pos, Transform3dTechnique::Rotate rotate) {
        setModel(pos);

        _model = glm::rotate(_model, glm::radians(rotate.angle), rotate.axis);
    }

    void Transform3dTechnique::setModel(glm::vec3 pos, glm::vec3 scale) {
        setModel(pos);

        _model = glm::scale(_model, scale);
    }

    void Transform3dTechnique::setModel(glm::vec3 pos, Transform3dTechnique::Rotate rotate,
                                        glm::vec3 scale) {
        setModel(pos);

        _model = glm::rotate(_model, glm::radians(rotate.angle), rotate.axis);
        _model = glm::scale(_model, scale);
    }

    void Transform3dTechnique::setView(glm::mat4 view) {
        _view = view;
    }

    void Transform3dTechnique::setModel(Transform3dTechnique::Rotate rotate) {
        _model = glm::mat4(1.0f);

        _model = glm::rotate(_model, glm::radians(rotate.angle), rotate.axis);
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

    glm::mat4 Transform3dTechnique::getModel() {
        return _model;
    }

    glm::mat4 Transform3dTechnique::getView() {
        return _view;
    }

    glm::mat4 Transform3dTechnique::getProjection() {
        return _projection;
    }

    void Transform3dTechnique::setRotate(Transform3dTechnique::Rotate rotate) {
        this->_rotate = rotate;

        _needRotate = true;
    }

    void Transform3dTechnique::setScale(glm::vec3 scale) {
        this->_scale = scale;

        _needScale = true;
    }

    void Transform3dTechnique::setTransform(glm::vec3 transform) {
        this->_transform = transform;
    }

    void Transform3dTechnique::calculateModel() {
        _model = glm::mat4(1.0f);
        _model = glm::translate(_model, _transform);

        if (_needRotate) {
            _model = glm::rotate(_model, glm::radians(_rotate.angle), _rotate.axis);
        }
        if (_needScale) {
            _model = glm::scale(_model, _scale);
        }
    }
}