#ifdef BUILD_TESTS

#include "CrossCalculator.h"
#include <unity.h>

void testCrossCalculator_find() {
    // Empty fields
    {
        const Fields fields;
        const Field field(Field::red);
        const Point point(3, 2);

        const auto pointList = CrossCalculator::find(fields, field, point);

        TEST_ASSERT_TRUE(pointList.empty());
    }

    // Finishing cross by putting field in the middle
    {
        Fields fields;
        const Field field(Field::red);
        const Point point(3, 2);

        fields[3][2] = field; // middle
        fields[4][2] = field; // bottom
        fields[2][2] = field; // top
        fields[3][3] = field; // right
        fields[3][1] = field; // left

        const auto pointList = CrossCalculator::find(fields, field, point);
        TEST_ASSERT_FALSE(pointList.empty());

        const auto& foundPoint = pointList[0];

        TEST_ASSERT_EQUAL_INT(3, foundPoint.y);
        TEST_ASSERT_EQUAL_INT(2, foundPoint.x);
    }

    // Not finished cross
    {
        Fields fields;
        const Field field(Field::red);
        const Point point(3, 2);

        fields[3][2] = field; // middle
        fields[4][2] = field; // bottom
        fields[2][2] = field; // top
        fields[3][3] = field; // right

        // This field is missing for cross to be finished
        // fields[3][1] = field;

        const auto pointList = CrossCalculator::find(fields, field, point);
        TEST_ASSERT_TRUE(pointList.empty());
    }

    // Finishing cross by putting field on left
    {
        Fields fields;
        const Field field(Field::red);
        const Point point(3, 1);

        fields[3][2] = field; // middle
        fields[4][2] = field; // bottom
        fields[2][2] = field; // top
        fields[3][3] = field; // right
        fields[3][1] = field; // left

        const auto pointList = CrossCalculator::find(fields, field, point);
        TEST_ASSERT_FALSE(pointList.empty());

        const auto& foundPoint = pointList[0];

        TEST_ASSERT_EQUAL_INT(3, foundPoint.y);
        TEST_ASSERT_EQUAL_INT(2, foundPoint.x);
    }

    // Cannot finish cross because one of the fields is in negatives
    {
        Fields fields;
        const Field field(Field::red);
        const Point point(0, 1);

        fields[0][2] = field; // middle
        fields[1][2] = field; // bottom

        fields[3][3] = field; // right
        fields[0][1] = field; // left

        const auto pointList = CrossCalculator::find(fields, field, point);
        TEST_ASSERT_TRUE(pointList.empty());
    }

    // Cannot finish cross because one of the fields is not same color
    {
        Fields fields;
        const Field field(Field::red);
        const Point point(3, 1);

        fields[3][2] = field; // middle
        fields[4][2] = field; // bottom

        fields[2][2] = field; // top
        fields[2][2].setType(Field::blue);

        fields[3][3] = field; // right
        fields[3][1] = field; // left

        const auto pointList = CrossCalculator::find(fields, field, point);
        TEST_ASSERT_TRUE(pointList.empty());
    }

    // Found two legitimate crosses one near another
    {
        Fields fields;
        const Field field(Field::red);
        const Point point(2, 2);

        fields[2][1] = field; // middle
        fields[3][1] = field; // bottom
        fields[1][1] = field; // top
        fields[2][2] = field; // right
        fields[2][0] = field; // left

        fields[2][3] = field; // middle
        fields[3][3] = field; // bottom
        fields[1][3] = field; // top
        fields[2][4] = field; // right
        fields[2][2] = field; // left

        const auto pointList = CrossCalculator::find(fields, field, point);
        TEST_ASSERT_EQUAL_INT(pointList.size(), 2);

        const auto& firstPoint = pointList[0];

        TEST_ASSERT_EQUAL_INT(2, firstPoint.y);
        TEST_ASSERT_EQUAL_INT(3, firstPoint.x);

        const auto& secondPoint = pointList[1];

        TEST_ASSERT_EQUAL_INT(2, secondPoint.y);
        TEST_ASSERT_EQUAL_INT(1, secondPoint.x);
    }

    // Two legitimate crosses interrupted by different color in middle
    {
        Fields fields;
        const Field field(Field::red);
        const Point point(2, 2);

        fields[2][1] = field; // middle
        fields[3][1] = field; // bottom
        fields[1][1] = field; // top
        fields[2][2] = field; // right
        fields[2][0] = field; // left

        fields[2][3] = field; // middle
        fields[3][3] = field; // bottom
        fields[1][3] = field; // top
        fields[2][4] = field; // right
        fields[2][2] = field; // left

        fields[2][2].setType(Field::purple);

        const auto pointList = CrossCalculator::find(fields, field, point);
        TEST_ASSERT_TRUE(pointList.empty());
    }

    // Found two semi-legitimate crosses one near another
    {
        Fields fields;
        const Field field(Field::red);
        const Point point(2, 2);

        fields[2][1] = field; // middle
        fields[3][1] = field; // bottom
        fields[1][1] = field; // top
        fields[2][2] = field; // right
        fields[2][0] = field; // left

        fields[2][2] = field; // middle
        fields[3][2] = field; // bottom
        fields[1][2] = field; // top
        fields[2][3] = field; // right
        fields[2][1] = field; // left

        const auto pointList = CrossCalculator::find(fields, field, point);
        TEST_ASSERT_EQUAL_INT(2, pointList.size());

        const auto& firstPoint = pointList[0];

        TEST_ASSERT_EQUAL_INT(2, firstPoint.y);
        TEST_ASSERT_EQUAL_INT(2, firstPoint.x);

        const auto& secondPoint = pointList[1];

        TEST_ASSERT_EQUAL_INT(2, secondPoint.y);
        TEST_ASSERT_EQUAL_INT(1, secondPoint.x);
    }

    // Cross cannot be made because one of the fields (which is not in the middle) is actually a building
    {
        Fields fields;
        const Field field(Field::red);
        const Point point(2, 2);

        fields[2][1] = field; // middle
        fields[3][1] = field; // bottom
        fields[1][1] = field; // top
        fields[2][2] = field; // right
        fields[2][0] = field; // left

        fields[2][0].upgrade();

        const auto pointList = CrossCalculator::find(fields, field, point);
        TEST_ASSERT_EQUAL_INT(0, pointList.size());
    }
}

void testCrossCalculator_upgrade() {
    // Empty fields
    {
        Fields fields;
        CrossCalculator::PointList pointList;

        CrossCalculator::upgrade(pointList, fields);

        TEST_ASSERT_TRUE(pointList.empty());
    }

    // One upgradable field
    {
        Fields fields;
        fields[2][1].setType(Field::blue);

        CrossCalculator::PointList pointList = { { 2, 1 } };

        CrossCalculator::upgrade(pointList, fields);

        TEST_ASSERT_EQUAL_INT(1, pointList.size());

        TEST_ASSERT_EQUAL_INT(2, pointList[0].y);
        TEST_ASSERT_EQUAL_INT(1, pointList[0].x);

        TEST_ASSERT_EQUAL_INT(Field::Building::levelFirst, fields[2][1].getBuilding());
    }

    // Two upgradable fields
    {
        Fields fields;
        fields[2][1].setType(Field::blue);
        fields[2][3].setType(Field::blue);
        fields[2][3].upgrade();

        CrossCalculator::PointList pointList = { { 2, 1 }, { 2, 3 } };

        CrossCalculator::upgrade(pointList, fields);

        TEST_ASSERT_EQUAL_INT(2, pointList.size());

        TEST_ASSERT_EQUAL_INT(2, pointList[0].y);
        TEST_ASSERT_EQUAL_INT(1, pointList[0].x);

        TEST_ASSERT_EQUAL_INT(2, pointList[1].y);
        TEST_ASSERT_EQUAL_INT(3, pointList[1].x);

        TEST_ASSERT_EQUAL_INT(Field::Building::levelFirst, fields[2][1].getBuilding());
        TEST_ASSERT_EQUAL_INT(Field::Building::levelSecond, fields[2][3].getBuilding());
    }

    // Two non-upgradable fields since they are adjacent
    {
        Fields fields;
        fields[2][1].setType(Field::blue);
        fields[2][2].setType(Field::blue);

        CrossCalculator::PointList pointList = { { 2, 1 }, { 2, 2 } };

        CrossCalculator::upgrade(pointList, fields);

        TEST_ASSERT_TRUE(pointList.empty());
    }
}

void testCrossCalculator_pay() {
    // Pay for two crosses
    {
        Fields fields;
        const Field field(Field::red);

        fields[2][1] = field; // middle
        fields[3][1] = field; // bottom
        fields[1][1] = field; // top
        fields[2][2] = field; // right
        fields[2][0] = field; // left

        fields[2][3] = field; // middle
        fields[3][3] = field; // bottom
        fields[1][3] = field; // top
        fields[2][4] = field; // right
        fields[2][2] = field; // left

        const CrossCalculator::PointList crossMiddleList = { { 2, 1 },
                                                             { 2, 3 } };

        CrossCalculator::FieldPointList modifiedFields;

        CrossCalculator::pay(crossMiddleList, fields, modifiedFields);

        TEST_ASSERT_EQUAL_INT(10, modifiedFields.size());

        TEST_ASSERT_EQUAL_INT(Field::red, fields[2][1].getType());
        TEST_ASSERT_EQUAL_INT(Field::black, fields[3][1].getType());
        TEST_ASSERT_EQUAL_INT(Field::black, fields[1][1].getType());
        TEST_ASSERT_EQUAL_INT(Field::black, fields[2][2].getType());
        TEST_ASSERT_EQUAL_INT(Field::black, fields[2][0].getType());

        TEST_ASSERT_EQUAL_INT(Field::red, fields[2][3].getType());
        TEST_ASSERT_EQUAL_INT(Field::black, fields[3][3].getType());
        TEST_ASSERT_EQUAL_INT(Field::black, fields[1][3].getType());
        TEST_ASSERT_EQUAL_INT(Field::black, fields[2][4].getType());
        TEST_ASSERT_EQUAL_INT(Field::black, fields[2][2].getType());
    }
}

#endif
