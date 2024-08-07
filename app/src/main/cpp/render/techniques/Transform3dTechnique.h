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
        struct Rotate {
            float angle{360.0f};
            glm::vec3 pivot{0.0f};
            glm::vec3 axis{0.0f};
        };

        using Ptr = std::shared_ptr<Transform3dTechnique>;

        Transform3dTechnique() = default;
        ~Transform3dTechnique() override = default;

        void execute(Shaders::ShaderProgram::Ptr shader) override;

        void setModel(glm::mat4);
        void setModel(glm::vec3 pos);
        void setModel(glm::vec3 pos, Rotate rotate);
        void setModel(Rotate rotate);
        void setModel(glm::vec3 pos, glm::vec3 scale);
        void setModel(glm::vec3 pos, Rotate rotate, glm::vec3 scale);

        void calculateModel();
        void setRotate(Rotate rotate);
        void setScale(glm::vec3 scale);
        void setTransform(glm::vec3 transform);

        void setView(glm::mat4 view);
        void setView(glm::vec3 pos);

        void setProjection(glm::mat4 projection);
        void setProjection(float angleDegrees, float screenWidth, float screenHeight, float zNear, float zFar);

        glm::mat4 getModel();
        glm::mat4 getView();
        glm::mat4 getProjection();
    private:
        glm::mat4 _model{1.0f};
        glm::mat4 _view {1.0f};
        glm::mat4 _projection{1.0f};

        Rotate _rotate;
        glm::vec3 _scale;
        glm::vec3 _transform;

        bool _needRotate = false;
        bool _needScale = false;
    };
}

#endif //CUBE_TRANSFORM3DTECHNIQUE_H
