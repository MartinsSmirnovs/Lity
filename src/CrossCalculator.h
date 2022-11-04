#pragma once

#include "LityConfig.h"
#include "Point.h"

class CrossCalculator {
public:
    using PointList      = std::vector<Point>;
    using FieldPoint     = std::pair<Field, Point>;
    using FieldPointList = std::vector<FieldPoint>;

    // Searches for crosses in fields list around specified field
    // Returns points which represent centers of found crosses
    static PointList find(const Fields& fields, const Field& field, const Point& point);

    // Upgrades fields in specified points. If point cannot be upgraded,
    // deletes it from passed list
    static void upgrade(PointList& crossMiddleList, Fields& fields);

    // Sets black fields around upgraded middle points of crosses
    // Returns list of fields to modify
    static FieldPointList price(const PointList& crossMiddleList, const Fields& fields);

private:
    constexpr static int fieldsInCross = 5;
    static const std::array<Point, fieldsInCross> searchValues;
};
