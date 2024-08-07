//
// Created by VeraTag on 03.08.2024.
//

#ifndef CUBE_PRIMITIVE_H
#define CUBE_PRIMITIVE_H

#include "buffers/Vao.h"

namespace Render::Primitives {
    struct Settings {
        bool withNormals = true;
        bool withTextureCoords = true;
        bool withTangent = true;
        bool withBitangent = true;
    };

    class Primitive {
    public:
        using Ptr = std::shared_ptr<Primitive>;

        explicit Primitive(const int& vertexNumber);
        explicit Primitive(const int& vertexNumber, const Settings &settings_);

        virtual ~Primitive() = default;

        virtual void bind();
        virtual void unbind();
        virtual void bindData(const unsigned int& bindFlag);
        virtual void draw();

        void setDrawCallback(std::function<void()> function);

        [[nodiscard]] unsigned int getUid() const;

    protected:
        void add(Buffers::ARaiiBuffer::Ptr raiiBuffer);

        std::vector<Buffers::ARaiiBuffer::Ptr> buffers{};
        Settings settings;

        const int vertexNumber;

    private:
        std::function<void()> _drawCallback;
        Buffers::Vao::Ptr _vao;
    };
} // Render

#endif //CUBE_PRIMITIVE_H
