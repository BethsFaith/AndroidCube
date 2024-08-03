//
// Created by VeraTag on 03.08.2024.
//

#include "ARaiiBuffer.h"

namespace Render::Buffers {
    ARaiiBuffer::ARaiiBuffer(const int &priority) : _priority(priority) {}

    unsigned int ARaiiBuffer::getPriority() const {
        return _priority;
    }
} // Buffers