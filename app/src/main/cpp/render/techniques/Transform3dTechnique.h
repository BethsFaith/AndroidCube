//
// Created by VeraTag on 06.08.2024.
//

#ifndef CUBE_TRANSFORM3DTECHNIQUE_H
#define CUBE_TRANSFORM3DTECHNIQUE_H

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ATechnique.h"

namespace Render::Techniques {
    class Transform3dTechnique : public ATechnique {
    public:
        using Ptr = std::shared_ptr<Transform3dTechnique>;

        Transform3dTechnique() = default;
        ~Transform3dTechnique() override = default;

        void execute(Shaders::ShaderProgram::Ptr shader) override;

        void setModel(glm::mat4);
        void setModel(float angleDegrees, glm::vec3 pos);

        void setView(glm::mat4 view);
        void setView(glm::vec3 pos);

        void setProjection(glm::mat4 projection);
        void setProjection(float angleDegrees, float screenWidth, float screenHeight, float zNear, float zFar);

    private:
        glm::mat4 _model{1.0f};
        glm::mat4 _view {1.0f};
        glm::mat4 _projection{1.0f};
    };
}

#endif //CUBE_TRANSFORM3DTECHNIQUE_H
