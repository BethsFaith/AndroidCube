//
// Created by VeraTag on 03.08.2024.
//

#ifndef CUBE_ARAIIBUFFER_H
#define CUBE_ARAIIBUFFER_H

#include <iostream>

#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>

namespace Render::Buffers {
    class ARaiiBuffer {
    public:
        using Ptr = std::shared_ptr<ARaiiBuffer>;

        explicit ARaiiBuffer(const int &priority);

        virtual ~ARaiiBuffer() = default;

        virtual void bind() = 0;

        virtual void unbind() = 0;

        virtual void bindData(const unsigned int &bindFlag) = 0;

        [[nodiscard]] unsigned int getPriority() const;

        [[nodiscard]] virtual unsigned int get() const = 0;

    private:
        unsigned int _priority;
    };

} // Buffers

#endif //CUBE_ARAIIBUFFER_H
