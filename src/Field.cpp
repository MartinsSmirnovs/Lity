#include "Field.h"
#include <stdexcept>

const std::vector<Field::Type> Field::typeList = {
    black,
    build3,
    build2,
    build1,
    white,
    blue,
    red,
    green,
    purple,
    eraser
};

const std::map<Field::Type, RGB> Field::typeColorMap = {
    { black, { 0, 0, 0 } },
    { white, { 50, 50, 50 } },
    { blue, { 0, 0, 255 } },
    { red, { 255, 0, 0 } },
    { green, { 0, 255, 0 } },
    { purple, { 255, 0, 255 } }
};

Field::Field(int value) {
    const auto targetIterator = closest(typeList, value);

    if (targetIterator == typeList.end()) {
        throw std::invalid_argument("Lower bound for value " + std::to_string(value) + " could not be found!");
    }

    const auto target = *targetIterator;

    if (!inRange(target, value)) {
        throw std::out_of_range("Value " + std::to_string(value) + " is out of range!");
    }

    type = target;
}

bool Field::inRange(Type target, int value) const {
    // Value too small
    if (target - digitalRange > value) {
        return false;
    }

    // Value too big
    if (target + digitalRange < value) {
        return false;
    }
    return true;
}

RGB Field::getColor() const {
    return typeColorMap.at(type);
}

auto Field::getType() const -> Field::Type {
    return type;
}

auto Field::closest(const TypeList& list, int value) const -> TypeList::const_iterator {
    const auto lowerBoundIterator = std::lower_bound(list.begin(),
                                                     list.end(),
                                                     value);

    if (lowerBoundIterator == list.end()) {
        return lowerBoundIterator;
    }

    const int previousValue = *(lowerBoundIterator - 1);
    const int currentValue  = *lowerBoundIterator;

    if (abs(value - previousValue) < abs(value - currentValue)) {
        return lowerBoundIterator - 1;
    }

    return lowerBoundIterator;
}
