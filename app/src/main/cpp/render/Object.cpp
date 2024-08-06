//
// Created by VeraTag on 03.08.2024.
//

#include "Object.h"

namespace Render {
    void Object::render(Shaders::ShaderProgram::Ptr& shaderProgram) {
        shaderProgram->use();

        for (const auto& pair : _techniques) {
            auto technique = pair.second;
            if (technique->isEnabled()) {
                technique->execute(shaderProgram);
            }
        }

        _primitive->draw();
    }

    void Object::addTechnique(Techniques::TechniqueType name, Techniques::ATechnique::Ptr technique) {
        _techniques[name] = std::move(technique);
    }

    void Object::removeTechnique(Techniques::TechniqueType name) {
        _techniques.erase(name);
    }

    void Object::enableTechnique(Techniques::TechniqueType name) {
        _techniques[name]->enable();
    }

    void Object::disableTechnique(Techniques::TechniqueType name) {
        _techniques[name]->disable();
    }

    bool Object::hasTechnique(Techniques::TechniqueType name) {
        return _techniques.find(name) != _techniques.end();
    }

    void Object::setPrimitive(const Primitives::Primitive::Ptr &primitive) {
        _primitive = primitive;
    }

    Techniques::ATechnique::Ptr Object::getTechnique(Techniques::TechniqueType name) {
        return _techniques[name];
    }

    Primitives::Primitive::Ptr Object::getPrimitive() {
        return _primitive;
    }
} // Render