#ifdef BUILD_TESTS

#include "LityConfig.h"
#include <Differ.h>
#include <unity.h>

void testDiffer_diff() {
    const FieldsRaw fieldsLeft  = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
    FieldsRaw fieldsRight = fieldsLeft;

    TEST_ASSERT_TRUE(Differ::diff(fieldsLeft, fieldsRight));

    fieldsRight[3] = 4;

    TEST_ASSERT_FALSE(Differ::diff(fieldsLeft, fieldsRight));
}

void testDiffer_find() {
    Fields fieldsLeft;
    fieldsLeft.fill({ 1, 1, 1, 1, 1 });

    Fields fieldsRight = fieldsLeft;

    {
        const auto coord = Differ::find(fieldsLeft, fieldsRight);
        TEST_ASSERT_TRUE(coord.isEmpty());
    }

    fieldsRight[2][3] = 0;

    {
        const auto coord = Differ::find(fieldsLeft, fieldsRight);
        TEST_ASSERT_EQUAL_INT(coord.y, 2);
        TEST_ASSERT_EQUAL_INT(coord.x, 3);
        TEST_ASSERT_TRUE(!coord.isEmpty());
    }
}

#endif
