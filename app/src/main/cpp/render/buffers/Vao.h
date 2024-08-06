//
// Created by VeraTag on 03.08.2024.
//

#ifndef CUBE_VAO_H
#define CUBE_VAO_H

#include "ARaiiBuffer.h"

namespace Render::Buffers {
    class Vao : public ARaiiBuffer {
    public:
        using Ptr = std::shared_ptr<Vao>;

        Vao();

        ~Vao() override;

        void bindData(const unsigned int &bindFlag) override;

        void bind() override;

        void unbind() override;

        [[nodiscard]] unsigned int get() const override;

    private:
        unsigned int _vao{};
    };
} // Buffers

#endif //CUBE_VAO_H
