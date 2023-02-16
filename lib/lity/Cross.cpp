#include "Cross.h"
#include "AnimationFactory.h"

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
        { Field::Type::any,    Field::black,    Field::Type::any },
        { Field::Type::black,  Field::target,   Field::Type::black },
        { Field::Type::any,    Field::black,    Field::Type::any }
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

bool Cross::find(const Fields& fields, const FieldPoint& fieldPoint) const {
    const auto& field = fieldPoint.first;
    const auto& point = fieldPoint.second;

    if (!checkBoundaries(fieldPoint, description.colorMask, description.center)) {
        return false;
    }

    if (!checkColorMask(fields, fieldPoint)) {
        return false;
    }

    if (!checkBuildingMask(fields, fieldPoint)) {
        return false;
    }

    return true;
}

auto Cross::apply(Fields& fields, const FieldPoint& fieldPoint) const -> AnimationList {
    applyPaymentMask(fields, fieldPoint);
    applyUpgradeMask(fields, fieldPoint);

    return createAnimationList(fieldPoint);
}

bool Cross::checkColorMask(const Fields& fields, const FieldPoint& fieldPoint) const {
    const auto& field = fieldPoint.first;
    const auto& point = fieldPoint.second;

    return checkMask(fieldPoint, description.colorMask, description.center, [&](int x, int y, Field::Type maskValue) {
        if (maskValue == Field::Type::any) {
            return true;
        }

        if (point.x == x && point.y == y) {
            return true;
        }

        if (fields[y][x].getType() == field.getType()) {
            return true;
        }

        return false;
    });
}

bool Cross::checkBuildingMask(const Fields& fields, const FieldPoint& fieldPoint) const {
    const auto& field = fieldPoint.first;
    const auto& point = fieldPoint.second;

    return checkMask(fieldPoint, description.buildingMask, description.center, [&](int x, int y, Building maskValue) {
        if (maskValue == Building::levelAny) {
            return true;
        }

        if (fields[y][x].getBuilding() == maskValue) {
            return true;
        }

        return false;
    });
}

auto Cross::createAnimationList(const FieldPoint& fieldPoint) const -> AnimationList {
    AnimationList animationList;

    applyMask(fieldPoint, description.animationMask, description.center, [&](int x, int y, Animation::Type maskValue) {
        if (maskValue == Animation::Type::none) {
            return;
        }

        animationList.emplace_back(maskValue, Point(y, x));
    });

    return animationList;
}

void Cross::applyUpgradeMask(Fields& fields, const FieldPoint& fieldPoint) const {
    const auto& field = fieldPoint.first;
    const auto& point = fieldPoint.second;

    applyMask(fieldPoint, description.colorMask, description.center, [&](int x, int y, bool maskValue) {
        if (maskValue) {
            fields[y][x].upgrade();
        }
    });
}

void Cross::applyPaymentMask(Fields& fields, const FieldPoint& fieldPoint) const {
    const auto& field = fieldPoint.first;
    const auto& point = fieldPoint.second;

    applyMask(fieldPoint, description.paymentMask, description.center, [&](int x, int y, Field::Type maskValue) {
        if (maskValue == Field::Type::any) {
            return;
        }

        if (maskValue == Field::Type::target) {
            fields[y][x].setType(field.getType());
            return;
        }

        fields[y][x].setType(maskValue);
    });
}
