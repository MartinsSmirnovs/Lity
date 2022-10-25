#ifdef BUILD_TESTS

#include "Point.h"
#include <unity.h>

void testPoint_isEmpty() {
    Point point;

    TEST_ASSERT_TRUE(point.isEmpty());

    point.x = 10;

    TEST_ASSERT_FALSE(point.isEmpty());
}

#endif
