#include "Dot.h"

Dot::Dot()
: Figure() {
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

    description.upgradeMask = {
        { 0 }
    };

    description.center = { 0, 0 };
}
