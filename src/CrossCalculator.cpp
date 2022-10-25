#include "CrossCalculator.h"

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
        std::array<Field::Type, fieldsInCross> cross;

        for (int i = 0; i < fieldsInCross; i++) {
            const auto resultPoint = point + searchPoint + searchValues[i];

            if (resultPoint.hasNegative()) {
                break;
            }

            const auto& resultField = fields[resultPoint.y][resultPoint.x];
            if (resultField.getType() != field.getType()) {
                break;
            }

            cross[i] = resultField.getType();
        }

        if (areAllElementsSame(cross)) {
            const auto crossMiddlePoint = point + searchPoint;
            pointList.push_back(crossMiddlePoint);
        }
    }

    return pointList;
}

void CrossCalculator::upgrade(PointList& crossMiddleList, Fields& fields) {
    if (crossMiddleList.empty()) {
        return;
    }

    for (int i = 0; i < crossMiddleList.size(); i++) {
        const auto& point = crossMiddleList[i];

        const bool upgraded = fields[point.y][point.x].upgrade();

        if (!upgraded) {
            crossMiddleList.erase(crossMiddleList.begin() + i);
            i--;
        }
    }
}

void CrossCalculator::pay(const PointList& crossMiddleList, Fields& fields, FieldPointList& resultList) {
    resultList.clear();

    for (const auto& point : crossMiddleList) {
        for (const auto& offset : searchValues) {
            if (offset == Point(0, 0)) {
                auto& field = fields[point.y][point.x];
                resultList.push_back({ field, point });
                continue;
            }

            const auto resultPoint = point + offset;

            auto& field = fields[resultPoint.y][resultPoint.x];
            field.setType(Field::black);

            resultList.push_back({ field, resultPoint });
        }
    }
}