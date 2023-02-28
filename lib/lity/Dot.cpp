#include "Dot.h"


Dot::Dot()
: Figure() {
    // clang-format off
    description.colorMask = {
        { Field::Type::target }
    };

    description.buildingMask = {
        { Building::levelAny }
    };

    description.paymentMask = {
        { Field::Type::target }
    };

    description.animationMask = {
        { Animation::Type::appearance },
    };
    // clang-format on

    description.upgradeMask = {
        { 0 }
    };

    description.center = { 0, 0 };
}
