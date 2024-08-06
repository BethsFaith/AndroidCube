//
// Created by VeraTag on 03.08.2024.
//

#ifndef CUBE_VERTEX_H
#define CUBE_VERTEX_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <GLES3/gl3.h>

namespace Render::Buffers {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 tex_coords;

        // Касательный вектор
        glm::vec3 tangent;
        // Вектор бинормали (вектор, перпендикулярный касательному вектору и вектору нормали)
        glm::vec3 bitangent;
    };

   void setVertexAttribute(const int& index, const int& size, const int& stride, void* offset);
} // Buffers

#endif //CUBE_VERTEX_H
