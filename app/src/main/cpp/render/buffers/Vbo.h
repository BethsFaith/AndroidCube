//
// Created by VeraTag on 03.08.2024.
//

#ifndef CUBE_VBO_H
#define CUBE_VBO_H

#include "ARaiiBuffer.h"
#include "Vertex.h"

namespace Render::Buffers {
    class Vbo : public ARaiiBuffer {
    public:
        using Ptr = std::shared_ptr<Vbo>;

        explicit Vbo(const std::vector<Vertex> &data);

        ~Vbo() override;

        void bind() override;

        void unbind() override;

        void bindData(const unsigned int &bindFlag) override;

        [[nodiscard]] unsigned int get() const override;

        [[nodiscard]] const std::vector<Vertex> &getVertices() const;

    private:
        unsigned int _vbo{};
        std::vector<Vertex> _vertices;
    };

} // Buffers

#endif //CUBE_VBO_H
