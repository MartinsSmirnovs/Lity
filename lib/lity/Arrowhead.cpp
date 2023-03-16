#include "Arrowhead.h"
#include "ScopedBackup.h"

Arrowhead::Arrowhead()
: Figure() {
    // clang-format off
    description.colorMask = {
        { Field::Type::any,    Field::any,    Field::Type::enemy },
        { Field::Type::target, Field::target, Field::Type::any   },
        { Field::Type::any,    Field::target, Field::Type::any   }
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

auto Arrowhead::apply(Fields& fields, const FieldPoint& fieldPoint) -> AnimationList {
    description.flip(foundDirection);
    return Figure::apply(fields, fieldPoint);
}

bool Arrowhead::find(const Fields& fields, const FieldPoint& fieldPoint) {
    searchByRotation(Direction::top, fields, fieldPoint);
    searchByRotation(Direction::left, fields, fieldPoint);
    searchByRotation(Direction::right, fields, fieldPoint);
    searchByRotation(Direction::bottom, fields, fieldPoint);

    return onlyOneFound;
}

void Arrowhead::searchByRotation(Direction direction, const Fields& fields, const FieldPoint& fieldPoint) {
    // Preserve original description, so all of them get rotated relative to same point
    const ScopedBackup descriptionBackup(description);

    description.flip(direction);
    const bool found = Figure::find(fields, fieldPoint);

    // If matched for more than one rotation
    if (found && onlyOneFound) {
        onlyOneFound = false;
        return;
    }

    if (found) {
        onlyOneFound   = true;
        foundDirection = direction;
    }
}
