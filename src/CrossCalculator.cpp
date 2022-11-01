#include "CrossCalculator.h"
#include "Differ.h"

const std::array<Point, CrossCalculator::fieldsInCross> CrossCalculator::searchValues = {
    Point(0, 0),  // middle
    Point(1, 0),  // bottom
    Point(-1, 0), // top
    Point(0, 1),  // right
    Point(0, -1)  // left
};

auto CrossCalculator::find(const Fields& fields, const Field& field, const Point& point) -> CrossCalculator::PointList {
    PointList pointList;

    for (const auto& searchPoint : searchValues) {
        std::array<Field::Type, fieldsInCross> cross = { Field::black,
                                                         Field::black,
                                                         Field::black,
                                                         Field::black,
                                                         Field::black };

        for (int i = 0; i < fieldsInCross; i++) {
            const auto resultPoint = point + searchPoint + searchValues[i];

            // If resulting point is out of the field (too small)
            if (resultPoint.hasNegative()) {
                break;
            }

            // If resulting point is out of the field (too big)
            if (resultPoint.y >= sideSize || resultPoint.x >= sideSize) {
                break;
            }

            const auto& resultField = fields[resultPoint.y][resultPoint.x];

            // If resulting point is of different color
            if (resultField.getType() != field.getType()) {
                break;
            }

            // If resulting point (which is not in the middle) is building
            if (!(searchValues[i].x == 0 && searchValues[i].y == 0)) {
                if (resultField.getBuilding() != Field::Building::levelNone) {
                    break;
                }
            }

            cross[i] = resultField.getType();
        }

        if (Differ::areAllElementsSame(cross)) {
            if (cross[0] == Field::black || cross[0] == Field::white) {
                continue;
            }

            const auto crossMiddlePoint = point + searchPoint;
            pointList.push_back(crossMiddlePoint);
        }
    }

    return pointList;
}

void CrossCalculator::upgrade(PointList& crossMiddleList, Fields& fields) {
    // If there are no crosses, return
    if (crossMiddleList.empty()) {
        return;
    }

    PointList resultList;

    for (int i = 0; i < crossMiddleList.size(); i++) {
        const auto& point = crossMiddleList[i];

        bool isAdjacent = false;
        for (int j = 0; j < crossMiddleList.size(); j++) {
            if (j == i) {
                continue;
            }

            const auto testPoint = point - crossMiddleList[j];

            // If two fields are adjacent
            if (abs(testPoint.y) + abs(testPoint.x) == 1) {
                isAdjacent = true;
                break;
            }
        }

        if (isAdjacent) {
            continue;
        }

        const bool upgraded = fields[point.y][point.x].upgrade();

        if (upgraded) {
            resultList.push_back(crossMiddleList[i]);
        }
    }

    crossMiddleList = resultList;
}

void CrossCalculator::pay(const PointList& crossMiddleList, Fields& fields, FieldPointList& modifiedFields) {
    modifiedFields.clear();

    for (const auto& point : crossMiddleList) {
        for (const auto& offset : searchValues) {
            if (offset == Point(0, 0)) {
                auto& field = fields[point.y][point.x];
                modifiedFields.push_back({ field, point });
                continue;
            }

            const auto resultPoint = point + offset;

            auto& field = fields[resultPoint.y][resultPoint.x];
            field.setType(Field::black);

            modifiedFields.push_back({ field, resultPoint });
        }
    }
}
