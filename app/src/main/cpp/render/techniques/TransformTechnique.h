//
// Created by VeraTag on 03.08.2024.
//

#ifndef CUBE_TRANSFORMTECHNIQUE_H
#define CUBE_TRANSFORMTECHNIQUE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ATechnique.h"

namespace Render::Techniques {
    class TransformTechnique : public ATechnique {
    public:
        struct Rotate {
            float angle{360.0f};
            glm::vec3 coordinates{0.0f};
        };

        using Ptr = std::shared_ptr<TransformTechnique>;

        TransformTechnique() = default;
        ~TransformTechnique() override = default;

        void execute(Shaders::ShaderProgram::Ptr shader) override;

        void enableTransform(const glm::vec3 &transformValue);
        void enableTransform();
        void disableTransform();

        void enableScale(const glm::vec3 &scaleValue);
        void enableScale();
        void disableScale();

        void enableRotateValue(const Rotate &rotateValue);
        void enableRotateValue();
        void disableRotateValue();

        [[nodiscard]] const glm::vec3 &getTransformValue() const;
        [[nodiscard]] const glm::vec3 &getScaleValue() const;
        [[nodiscard]] const Rotate &getRotateValue() const;
        void setTransformValue(const glm::vec3& transformValue);
        void setScaleValue(const glm::vec3& scaleValue);
        void setRotateValue(const Rotate& rotateValue);

    private:
        bool _needRotate = false;
        bool _needScale = false;
        bool _needTransform = false;

        glm::vec3 _transformValue{0.0f};
        glm::vec3 _scaleValue{0.0f};
        Rotate _rotateValue{};
    };
} // Techniques

#endif //CUBE_TRANSFORMTECHNIQUE_H
