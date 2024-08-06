//
// Created by VeraTag on 03.08.2024.
//

#include "Vao.h"

namespace Render::Buffers {
    Vao::Vao() : ARaiiBuffer(0)  {
        glGenVertexArrays(1, &_vao);
    }

    Vao::~Vao()  {
        glDeleteVertexArrays(1, &_vao);
    }

    void Vao::bind() {
        glBindVertexArray(_vao);
    }

    void Vao::bindData(const unsigned int& bindFlag) {}

    void Vao::unbind() {
        glBindVertexArray(0);
    }

    unsigned int Vao::get() const {
        return _vao;
    }
} // Render::Buffers
