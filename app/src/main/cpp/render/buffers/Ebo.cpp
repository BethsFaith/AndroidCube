//
// Created by VeraTag on 03.08.2024.
//

#include "Ebo.h"

namespace Render::Buffers {
    Ebo::Ebo(std::vector<unsigned int>& indices) : ARaiiBuffer(2), _indices(indices) {
        glGenBuffers(1, &_ebo);
    }

    Ebo::~Ebo() {
        glDeleteBuffers(1, &_ebo);
    }

    void Ebo::bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    }

    void Ebo::unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Ebo::bindData(const unsigned int& bindFlag) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(float), &_indices[0], bindFlag);
    }

    unsigned int Ebo::get() const {
        return _ebo;
    }

    const std::vector<unsigned int>& Ebo::getIndices() const {
        return _indices;
    }
} // Buffers