#ifdef BUILD_TESTS

#include "Coord.h"
#include <unity.h>

void testCoord_isEmpty() {
    Coord coord;

    TEST_ASSERT_TRUE(coord.isEmpty());

    coord.x = 10;

    TEST_ASSERT_FALSE(coord.isEmpty());
}

#endif
