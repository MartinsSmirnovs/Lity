#ifdef BUILD_TESTS

#include "Differ.h"
#include "LityConfig.h"
#include <unity.h>

void testDiffer_diff() {
    const FieldsRaw fieldsLeft = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
    FieldsRaw fieldsRight      = fieldsLeft;

    TEST_ASSERT_TRUE(Differ::equal(fieldsLeft, fieldsRight));

    fieldsRight[3] = 4;

    TEST_ASSERT_FALSE(Differ::equal(fieldsLeft, fieldsRight));
}

#endif
