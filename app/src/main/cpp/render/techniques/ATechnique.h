//
// Created by VeraTag on 03.08.2024.
//

#ifndef CUBE_ATECHNIQUE_H
#define CUBE_ATECHNIQUE_H

#include "Shader.h"

namespace Render::Techniques {
    class ATechnique {
    public:
        using Ptr = std::shared_ptr<ATechnique>;

        ATechnique() = default;
        virtual ~ATechnique() = default;

        virtual void execute(Shader::Ptr shader) = 0;

        void enable();
        void disable();

        [[nodiscard]] bool isEnabled() const;

    private:
        bool _enabled = true;
    };
} // Render::Techniques

#endif //CUBE_ATECHNIQUE_H
