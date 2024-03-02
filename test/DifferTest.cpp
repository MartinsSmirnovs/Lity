#include "Differ.h"
#include "LityConfig.h"
#include <unity.h>

void testDiffer_equal()
{
    const FieldsRaw fieldsLeft = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
    FieldsRaw fieldsRight = fieldsLeft;

    TEST_ASSERT_TRUE( Differ::equal( fieldsLeft, fieldsRight ) );

    fieldsRight[ 3 ] = 4;

    TEST_ASSERT_FALSE( Differ::equal( fieldsLeft, fieldsRight ) );
}

void testDiffer_diff()
{
    const FieldsRaw fieldsLeft = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
    FieldsRaw fieldsRight = fieldsLeft;

    {
        const auto diff = Differ::diff( fieldsLeft, fieldsRight );
        TEST_ASSERT_EQUAL_INT( Differ::noDifference, diff.first );
    }

    fieldsRight[ 12 ] = 10;

    {
        const auto diff = Differ::diff( fieldsLeft, fieldsRight );
        TEST_ASSERT_EQUAL_INT( 12, diff.first );
        TEST_ASSERT_EQUAL_INT( 10, diff.second );
    }
}

void testDiffer_areAllElementsSame()
{
    FieldsRaw values = {};

    TEST_ASSERT_TRUE( Differ::areAllElementsSame( values ) );

    values[ 3 ] = 4;

    TEST_ASSERT_FALSE( Differ::areAllElementsSame( values ) );
}
