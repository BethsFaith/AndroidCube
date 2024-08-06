//
// Created by VeraTag on 03.08.2024.
//

#include "ATechnique.h"

namespace Render::Techniques {

    void ATechnique::enable() {
        _enabled = true;
    }

    void ATechnique::disable() {
        _enabled = false;
    }

    bool ATechnique::isEnabled() const {
        return _enabled;
    }
}