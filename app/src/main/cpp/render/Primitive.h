//
// Created by VeraTag on 03.08.2024.
//

#ifndef CUBE_PRIMITIVE_H
#define CUBE_PRIMITIVE_H

#include "buffers/Vao.h"

namespace Render {
    struct Settings {
        bool with_normals = true;
        bool with_texture_coords = true;
        bool with_tangent = true;
        bool with_bitangent = true;
    };

    class Primitive {
    public:
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
