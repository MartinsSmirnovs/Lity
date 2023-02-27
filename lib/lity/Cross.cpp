#include "Cross.h"

Cross::Cross()
: Figure() {
    // clang-format off
    description.colorMask = {
        { Field::Type::any,    Field::target, Field::Type::any },
        { Field::Type::target, Field::target, Field::Type::target },
        { Field::Type::any,    Field::target, Field::Type::any }
    };

    description.buildingMask = {
        { Building::levelAny,  Building::levelNone, Building::levelAny },
        { Building::levelNone, Building::levelNone, Building::levelNone },
        { Building::levelAny,  Building::levelNone, Building::levelAny }
    };

    description.paymentMask = {
        { Field::Type::any,   Field::Type::black,  Field::Type::any },
        { Field::Type::black, Field::Type::target, Field::Type::black },
        { Field::Type::any,   Field::Type::black,  Field::Type::any }
    };

    description.animationMask = {
        { Animation::Type::none,     Animation::Type::payment,      Animation::Type::none },
        { Animation::Type::payment,  Animation::Type::appearance,   Animation::Type::payment },
        { Animation::Type::none,     Animation::Type::payment,      Animation::Type::none },
    };
    // clang-format on

    description.upgradeMask = {
        { 0, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 0 }
    };

    description.center = { 1, 1 };
}
