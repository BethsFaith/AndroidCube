//
// Created by VeraTag on 03.08.2024.
//

#include "Vertex.h"

namespace Render::Buffers {
    void setVertexAttribute(const int& index, const int& size, const int& stride, void* offset) {
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(index);
    }
} // Buffers