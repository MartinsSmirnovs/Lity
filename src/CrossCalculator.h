#pragma once

#include "LityConfig.h"
#include "Point.h"

class CrossCalculator {
public:
    using PointList      = std::vector<Point>;
    using FieldPointList = std::vector<std::pair<Field, Point>>;

    static PointList find(const Fields& fields, const Field& field, const Point& point);

    static void upgrade(PointList& crossMiddleList, Fields& fields);

    static void pay(const PointList& crossMiddleList, Fields& fields, FieldPointList& resultList);

private:
    constexpr static int fieldsInCross = 5;
    static const std::array<Point, fieldsInCross> searchValues;

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
