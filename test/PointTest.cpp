#ifdef BUILD_TESTS

#include "Point.h"
#include <unity.h>

void testPoint_Constructor() {
    {
        const Point point;
        TEST_ASSERT_EQUAL_INT(Point::empty, point.x);
        TEST_ASSERT_EQUAL_INT(Point::empty, point.y);
    }

    {
        const Point point(2, 3);
        TEST_ASSERT_EQUAL_INT(2, point.y);
        TEST_ASSERT_EQUAL_INT(3, point.x);
    }
}

void testPoint_isEmpty() {
    Point point;
    TEST_ASSERT_TRUE(point.isEmpty());

    point.x = 4;
    TEST_ASSERT_FALSE(point.isEmpty());
}

void testPoint_hasNegative() {
    Point point;

    TEST_ASSERT_TRUE(point.hasNegative());

    point.x = 1;
    TEST_ASSERT_TRUE(point.hasNegative());

    point.y = 3;
    TEST_ASSERT_FALSE(point.hasNegative());
}

void testPoint_operatorPlus() {
    {
        const Point first(2, 3);
        const Point second(1, 2);

        const auto result = first + second;

        TEST_ASSERT_EQUAL_INT(3, result.y);
        TEST_ASSERT_EQUAL_INT(5, result.x);
    }

    {
        {
            const Point first;
            const Point second(-3, 2);

            const auto result = first + second;

            TEST_ASSERT_EQUAL_INT(-4, result.y);
            TEST_ASSERT_EQUAL_INT(1, result.x);
        }
    }
}

void testPoint_OperatorEquals() {
    const Point first;
    const Point second;

    TEST_ASSERT_TRUE(first == second);
}

void testPoint_ConstructorEqualsNot() {
    const Point first(1, 0);
    const Point second;

    TEST_ASSERT_TRUE(first != second);
}

#endif
