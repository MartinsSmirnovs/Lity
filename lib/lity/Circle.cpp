#include "Circle.h"

Circle::Circle()
: Figure()
{
    // clang-format off
    description.colorMask = {
        { Field::Type::any,    Field::Type::any,    Field::target, Field::Type::any,    Field::Type::any },
        { Field::Type::any,    Field::Type::target, Field::target, Field::Type::target, Field::Type::any },
        { Field::Type::target, Field::Type::target, Field::target, Field::Type::target, Field::Type::target },
        { Field::Type::any,    Field::Type::target, Field::target, Field::Type::target, Field::Type::any },
        { Field::Type::any,    Field::Type::any,    Field::target, Field::Type::any,    Field::Type::any },
    };

    description.buildingMask = {
        { Building::levelAny, Building::levelAny,  Building::levelAny,    Building::levelAny,  Building::levelAny },
        { Building::levelAny, Building::levelAny,  Building::levelNone,   Building::levelAny,  Building::levelAny },
        { Building::levelAny, Building::levelNone, Building::levelSecond, Building::levelNone, Building::levelAny },
        { Building::levelAny, Building::levelAny,  Building::levelNone,   Building::levelAny,  Building::levelAny },
        { Building::levelAny, Building::levelAny,  Building::levelAny,    Building::levelAny,  Building::levelAny }
    };

    description.paymentMask = {
        { Field::Type::any,    Field::Type::any,   Field::Type::target, Field::any,   Field::Type::any },
        { Field::Type::any,    Field::Type::black, Field::Type::black,  Field::black, Field::Type::any },
        { Field::Type::target, Field::Type::black, Field::Type::target, Field::black, Field::Type::target },
        { Field::Type::any,    Field::Type::black, Field::Type::black,  Field::black, Field::Type::any },
        { Field::Type::any,    Field::Type::any,   Field::Type::target, Field::any,   Field::Type::any }
    };

    description.animationMask = {
        { Animation::Type::none, Animation::Type::none,    Animation::Type::none,       Animation::Type::none,    Animation::Type::none },
        { Animation::Type::none, Animation::Type::payment, Animation::Type::payment,    Animation::Type::payment, Animation::Type::none },
        { Animation::Type::none, Animation::Type::payment, Animation::Type::appearance, Animation::Type::payment, Animation::Type::none },
        { Animation::Type::none, Animation::Type::payment, Animation::Type::payment,    Animation::Type::payment, Animation::Type::none },
        { Animation::Type::none, Animation::Type::none,    Animation::Type::none,       Animation::Type::none,    Animation::Type::none }
    };
    // clang-format on

    description.upgradeMask = {
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 }
    };

    description.center = { 2, 2 };
}
