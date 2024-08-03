//
// Created by VeraTag on 03.08.2024.
//

#include "Vbo.h"

namespace Render::Buffers {
    Vbo::Vbo(const std::vector<Vertex>& data) : ARaiiBuffer(1),
                                                   _vertices(data) {
        glGenBuffers(1, &_vbo);
    }

    Vbo::~Vbo() {
        glDeleteBuffers(1, &_vbo);
    }

    void Vbo::bind() {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    }

    void Vbo::bindData(const unsigned int& bindFlag) {
        glBufferData(GL_ARRAY_BUFFER,
                     int(_vertices.size() * sizeof(Vertex)),
                     &_vertices[0],
                     bindFlag);    //_data.data(), bind_flag);
    }

    void Vbo::unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    unsigned int Vbo::get() const {
        return _vbo;
    }

    const std::vector<Vertex>& Vbo::getVertices() const {
        return _vertices;
    }
} // Render::Buffers
