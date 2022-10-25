#include "Differ.h"
#include <algorithm>

bool Differ::equal(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight) {
    return std::equal(fieldsLeft.begin(), fieldsLeft.end(), fieldsRight.begin());
}

Point Differ::find(const Fields& fieldsLeft, const Fields& fieldsRight) {
    const auto missmatchY = std::mismatch(fieldsLeft.begin(), fieldsLeft.end(), fieldsRight.begin());

    // If there is no mismatch, return empty pointinate
    if (missmatchY.first == fieldsLeft.end()) {
        return Point();
    }

    const auto missmatchX = std::mismatch(missmatchY.first->begin(), missmatchY.first->end(), missmatchY.second->begin());

    Point point;
    // Difference between pointers is values of pointinate
    point.y = missmatchY.first - fieldsLeft.begin();
    point.x = missmatchX.first - missmatchY.first->begin();

    return point;
}

std::pair<int, uint16_t> Differ::diff(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight) {
    std::pair<int, uint16_t> diff;
    diff.first  = noDifference;
    diff.second = noDifference;

    for (int i = 0; i < fieldsLeft.size(); i++) {
        if (fieldsLeft[i] != fieldsRight[i]) {
            diff.first  = i;
            diff.second = fieldsRight[i];
            return diff;
        }
    }

    return diff;
}