//
// Created by VeraTag on 03.08.2024.
//

#ifndef CUBE_EBO_H
#define CUBE_EBO_H

#include "ARaiiBuffer.h"

namespace Render::Buffers {
    class Ebo : public ARaiiBuffer {
    public:
        using Ptr = std::shared_ptr<Ebo>;

        explicit Ebo(std::vector<unsigned int>& indices);

        ~Ebo() override;

        void bind() override;

        void unbind() override;

        void bindData(const unsigned int &bindFlag) override;

        [[nodiscard]] unsigned int get() const override;

        [[nodiscard]] const std::vector<unsigned int> &getIndices() const;

    private:
        unsigned int _ebo{};

        std::vector<unsigned int> _indices;
    };
} // Render::Buffers

#endif //CUBE_EBO_H
