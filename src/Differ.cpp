#include "Differ.h"
#include <algorithm>

bool Differ::equal(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight) {
    return std::equal(fieldsLeft.begin(), fieldsLeft.end(), fieldsRight.begin());
}

Coord Differ::find(const Fields& fieldsLeft, const Fields& fieldsRight) {
    const auto missmatchY = std::mismatch(fieldsLeft.begin(), fieldsLeft.end(), fieldsRight.begin());

    // If there is no mismatch, return empty coordinate
    if (missmatchY.first == fieldsLeft.end()) {
        return Coord();
    }

    const auto missmatchX = std::mismatch(missmatchY.first->begin(), missmatchY.first->end(), missmatchY.second->begin());

    Coord coord;
    // Difference between pointers is values of coordinate
    coord.y = missmatchY.first - fieldsLeft.begin();
    coord.x = missmatchX.first - missmatchY.first->begin();

    return coord;
}