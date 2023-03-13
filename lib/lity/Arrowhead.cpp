#include "Arrowhead.h"

Arrowhead::Arrowhead()
: Figure() {
    // clang-format off
    description.colorMask = {
        { Field::Type::any,    Field::any,    Field::Type::any },
        { Field::Type::target, Field::target, Field::Type::any },
        { Field::Type::any,    Field::target, Field::Type::any }
    };

    description.buildingMask = {
        { Building::levelAny,  Building::levelAny,  Building::levelNone },
        { Building::levelNone, Building::levelNone, Building::levelAny },
        { Building::levelAny,  Building::levelNone, Building::levelAny }
    };

    description.paymentMask = {
        { Field::Type::any, Field::Type::any,   Field::Type::target },
        { Field::Type::any, Field::Type::white, Field::Type::any },
        { Field::Type::any, Field::Type::any,   Field::Type::any }
    };

    description.animationMask = {
        { Animation::Type::none, Animation::Type::none,       Animation::Type::payment },
        { Animation::Type::none, Animation::Type::appearance, Animation::Type::none },
        { Animation::Type::none, Animation::Type::none,       Animation::Type::none },
    };
    // clang-format on

    description.upgradeMask = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    description.center = { 1, 1 };
}

Arrowhead::Arrowhead(Direction direction)
: Arrowhead() {
    description.flip(direction);
}
