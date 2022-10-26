#pragma once

#include "LityConfig.h"
#include "Point.h"

class Differ {
public:
    static bool equal(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight);

    constexpr static int noDifference = -1;
    // If no diff, pair::first will be -1
    static std::pair<int, uint16_t> diff(const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight);

    template <class T>
    static bool areAllElementsSame(const T& container) {
        if (container.size() == 0) {
            return true;
        }

        const auto& first = container[0];

        for (const auto& i : container) {
            if (i != first) {
                return false;
            }
        }

        return true;
    }
};