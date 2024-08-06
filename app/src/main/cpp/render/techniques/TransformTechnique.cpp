//
// Created by VeraTag on 03.08.2024.
//

#include "TransformTechnique.h"

namespace Render::Techniques {
    void TransformTechnique::execute(Shaders::ShaderProgram::Ptr shader) {
        glm::mat4 trans = glm::mat4(1.0f);
        if (_needTransform) {
            trans = glm::translate(trans, _transformValue);
        }
        if (_needRotate) {
            trans = glm::rotate(trans, glm::radians(_rotateValue.angle), _rotateValue.coordinates);
        }
        if (_needScale) {
            trans = glm::scale(trans, _scaleValue);
        }

        shader->set4FloatMat("Transform", glm::value_ptr(trans));
    }

    void TransformTechnique::enableTransform(const glm::vec3& transformValue) {
        _transformValue = transformValue;
        _needTransform = true;
    }

    void TransformTechnique::enableTransform() {
        _needTransform = true;
    }

    void TransformTechnique::disableTransform() {
        _needTransform = false;
    }

    void TransformTechnique::enableScale(const glm::vec3& scaleValue) {
        _scaleValue = scaleValue;
        _needScale = true;
    }

    void TransformTechnique::enableScale() {
        _needScale = true;
    }

    void TransformTechnique::disableScale() {
        _needScale = false;
    }

    void TransformTechnique::enableRotateValue(const Rotate& rotateValue) {
        _rotateValue = rotateValue;
        _needRotate = true;
    }

    void TransformTechnique::enableRotateValue() {
        _needRotate = true;
    }

    void TransformTechnique::disableRotateValue() {
        _needRotate = false;
    }

    const glm::vec3& TransformTechnique::getTransformValue() const {
        return _transformValue;
    }

    const glm::vec3& TransformTechnique::getScaleValue() const {
        return _scaleValue;
    }

    const TransformTechnique::Rotate& TransformTechnique::getRotateValue() const {
        return _rotateValue;
    }

    void TransformTechnique::setTransformValue(const glm::vec3& transformValue) {
        _transformValue = transformValue;
    }

    void TransformTechnique::setScaleValue(const glm::vec3& scaleValue) {
        _scaleValue = scaleValue;
    }

    void TransformTechnique::setRotateValue(const TransformTechnique::Rotate& rotateValue) {
        _rotateValue = rotateValue;
    }
} // Techniques