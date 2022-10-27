#pragma once

#include "LityConfig.h"
#include "Point.h"

class CrossCalculator {
public:
    using PointList      = std::vector<Point>;
    using FieldPointList = std::vector<std::pair<Field, Point>>;

    // Searches for crosses in fields list around specified field
    // Returns points which represent centers of found crosses
    static PointList find(const Fields& fields, const Field& field, const Point& point);

    // Upgrades fields in specified points. If point cannot be upgraded,
    // deletes it from passed list
    static void upgrade(PointList& crossMiddleList, Fields& fields);

    // Sets black fields around upgraded middle points of crosses
    // Writes into modifiedFields to indicate amount of payment
    static void pay(const PointList& crossMiddleList, Fields& fields, FieldPointList& modifiedFields);

private:
    constexpr static int fieldsInCross = 5;
    static const std::array<Point, fieldsInCross> searchValues;
};
