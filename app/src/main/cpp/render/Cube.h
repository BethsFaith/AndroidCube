//
// Created by VeraTag on 03.08.2024.
//

#ifndef CUBE_CUBE_H
#define CUBE_CUBE_H

#include "Primitive.h"
#include "buffers/Vbo.h"
#include "buffers/Ebo.h"
#include "buffers/Vertex.h"

namespace Render {
    class Cube : public Primitive {
    public:
        explicit Cube(const Settings &settings);

        ~Cube() override = default;

        void draw() override;

        void bindData(const unsigned int& bind_flag) override;
    private:
        static std::vector<glm::vec3> getPosition();
        static std::vector<glm::vec3> getNormals();
        static std::vector<glm::vec2> getTextureCoordinates();
    };
} // Render

#endif //CUBE_CUBE_H
