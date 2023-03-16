#include "Figure.h"

bool Figure::find(const Fields& fields, const FieldPoint& fieldPoint) {
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

auto Figure::apply(Fields& fields, const FieldPoint& fieldPoint) -> AnimationList {
    applyPaymentMask(fields, fieldPoint);
    applyUpgradeMask(fields, fieldPoint);

    return createAnimationList(fieldPoint);
}

bool Figure::checkColorMask(const Fields& fields, const FieldPoint& fieldPoint) const {
    const auto& field = fieldPoint.first;
    const auto& point = fieldPoint.second;

    return checkMask(fieldPoint, description.colorMask, description.center, [&](int x, int y, Field::Type maskValue) {
        if (maskValue == Field::Type::any) {
            return true;
        }

        // Match any enemy color
        if (maskValue == Field::Type::enemy &&
            fields[y][x].getType() != field.getType() &&
            fields[y][x].getType() != Field::Type::black &&
            fields[y][x].getType() != Field::Type::white) {
            return true;
        }

        // Do not match if enemy mask is at target position
        if (maskValue == Field::Type::enemy &&
            fields[y][x].getType() == field.getType()) {
            return false;
        }

        // Match current field
        if (point.x == x && point.y == y) {
            return true;
        }

        // Match existing field at position with current field
        if (fields[y][x].getType() == field.getType()) {
            return true;
        }

        return false;
    });
}

bool Figure::checkBuildingMask(const Fields& fields, const FieldPoint& fieldPoint) const {
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

void Figure::applyUpgradeMask(Fields& fields, const FieldPoint& fieldPoint) const {
    const auto& field = fieldPoint.first;
    const auto& point = fieldPoint.second;

    applyMask(fieldPoint, description.upgradeMask, description.center, [&](int x, int y, bool maskValue) {
        if (maskValue) {
            fields[y][x].upgrade();
        }
    });
}

void Figure::applyPaymentMask(Fields& fields, const FieldPoint& fieldPoint) const {
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

auto Figure::createAnimationList(const FieldPoint& fieldPoint) const -> AnimationList {
    AnimationList animationList;

    applyMask(fieldPoint, description.animationMask, description.center, [&](int x, int y, Animation::Type maskValue) {
        if (maskValue == Animation::Type::none) {
            return;
        }

        animationList.emplace_back(maskValue, Point(y, x));
    });

    return animationList;
}
