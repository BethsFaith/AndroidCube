//
// Created by VeraTag on 03.08.2024.
//

#ifndef CUBE_OBJECT_H
#define CUBE_OBJECT_H

#include <map>

#include "primitives/Primitive.h"
#include "techniques/ATechnique.h"
#include "techniques/TechniqueType.h"

namespace Render {
    class Object {
    public:
        using Ptr = std::shared_ptr<Object>;

        Object() = default;
        virtual ~Object() = default;

        virtual void render(Shaders::ShaderProgram::Ptr& shaderProgram);

        void addTechnique(Techniques::TechniqueType type, Techniques::ATechnique::Ptr technique);
        void removeTechnique(Techniques::TechniqueType type);
        void enableTechnique(Techniques::TechniqueType type);
        void disableTechnique(Techniques::TechniqueType type);
        bool hasTechnique(Techniques::TechniqueType type);

        void setPrimitive(const Primitives::Primitive::Ptr &primitive);

        Techniques::ATechnique::Ptr getTechnique(Techniques::TechniqueType type);
        Primitives::Primitive::Ptr getPrimitive();

    private:
        std::map<Techniques::TechniqueType, Techniques::ATechnique::Ptr> _techniques;

        Primitives::Primitive::Ptr _primitive;
    };

} // Object

#endif //CUBE_OBJECT_H
