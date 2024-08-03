//
// Created by VeraTag on 03.08.2024.
//

#ifndef CUBE_PCUBE_H
#define CUBE_PCUBE_H

#include "Primitive.h"
#include "buffers/Vbo.h"
#include "buffers/Ebo.h"
#include "buffers/Vertex.h"

namespace Render::Primitives {
    class PCube : public Primitive {
    public:
        explicit PCube(const Settings &settings);

        ~PCube() override = default;

        void draw() override;

        void bindData(const unsigned int& bind_flag) override;
    private:
        static std::vector<glm::vec3> getPosition();
        static std::vector<glm::vec3> getNormals();
        static std::vector<glm::vec2> getTextureCoordinates();
    };
} // Render

#endif //CUBE_PCUBE_H
