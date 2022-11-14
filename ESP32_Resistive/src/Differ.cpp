#include "Differ.h"
#include <algorithm>

bool Differ::equal(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight) {
    return std::equal(fieldsLeft.begin(), fieldsLeft.end(), fieldsRight.begin());
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