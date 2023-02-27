#include "Square.h"

Square::Square()
: Figure() {
    // clang-format off
    description.colorMask = {
        { Field::Type::target, Field::target, Field::Type::target },
        { Field::Type::target, Field::target, Field::Type::target },
        { Field::Type::target, Field::target, Field::Type::target }
    };

    description.buildingMask = {
        { Building::levelAny,  Building::levelNone, Building::levelAny },
        { Building::levelNone, Building::levelNone, Building::levelNone },
        { Building::levelAny,  Building::levelNone, Building::levelAny }
    };

    description.paymentMask = {
        { Field::Type::target, Field::Type::black,  Field::Type::target },
        { Field::Type::black,  Field::Type::target, Field::Type::black },
        { Field::Type::target, Field::Type::black,  Field::Type::target }
    };

    description.animationMask = {
        { Animation::Type::none,    Animation::Type::payment,    Animation::Type::none },
        { Animation::Type::payment, Animation::Type::appearance, Animation::Type::payment },
        { Animation::Type::none,    Animation::Type::payment,    Animation::Type::none },
    };
    // clang-format on

    description.upgradeMask = {
        { 0, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 0 }
    };

    description.center = { 1, 1 };
}
