//
// Created by VeraTag on 03.08.2024.
//

#include "Primitive.h"

namespace Render::Primitives {
    Primitive::Primitive(const int &vertexNumber) : Primitive(vertexNumber, {}) {}

    Primitive::Primitive(const int &vertexNumber, const Settings &settings_) : vertexNumber(vertexNumber), settings(settings_) {
        _drawCallback = []() {};

        _vao = std::make_shared<Buffers::Vao>();
        add(_vao);
    }

    void Primitive::bind() {
        _vao->bind();
    }

    void Primitive::unbind() {
        _vao->unbind();
    }

    void Primitive::bindData(const unsigned int& bindFlag) {
        for (auto& buffer : buffers) {
            buffer->bind();
            buffer->bindData(bindFlag);
        }
    }

    void Primitive::draw() {
        bind();

        _drawCallback();
    }

    void Primitive::add(Buffers::ARaiiBuffer::Ptr raiiBuffer) {
        buffers.push_back(std::move(raiiBuffer));

        std::sort(buffers.begin(),
                  buffers.end(),
                  [](const Buffers::ARaiiBuffer::Ptr& buf1, const Buffers::ARaiiBuffer::Ptr& buf2) {
                      return buf1->getPriority() < buf2->getPriority();
                  });
    }

    void Primitive::setDrawCallback(std::function<void()> function) {
        _drawCallback = std::move(function);
    }

    unsigned int Primitive::getUid() const {
        return _vao->get();
    }
} // Render