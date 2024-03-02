#include "Field.h"
#include <unity.h>

void testField_constructor()
{
    static_assert( Field::green == 2457 );
    static_assert( Field::blue == 738 );

    // Lower bound exception test
    {
        try
        {
            const Field field( 4095 );
        }
        catch ( const std::exception& exception )
        {
            TEST_ASSERT_EQUAL_STRING( "Lower bound for value 4095 could not be found!", exception.what() );
        }
    }

    // Blue value out of range because too big test
    {
        try
        {
            const Field field( 950 );
        }
        catch ( const std::exception& exception )
        {
            TEST_ASSERT_EQUAL_STRING( "Value 950 is out of range!", exception.what() );
        }
    }

    // Blue value out of range because too small test
    {
        try
        {
            const Field field( 400 );
        }
        catch ( const std::exception& exception )
        {
            TEST_ASSERT_EQUAL_STRING( "Value 400 is out of range!", exception.what() );
        }
    }

    // Slightly bigger but in range white value test
    {
        try
        {
            const Field field( 2557 );

            TEST_ASSERT_EQUAL_INT( Field::green, field.getType() );

            const auto rgb = field.getColor();
            TEST_ASSERT_EQUAL_INT( 0, rgb.red );
            TEST_ASSERT_EQUAL_INT( 255, rgb.green );
            TEST_ASSERT_EQUAL_INT( 0, rgb.blue );
        }
        catch ( const std::exception& exception )
        {
            TEST_FAIL_MESSAGE( exception.what() );
        }
    }

    // Slightly smaller but in range white value test
    {
        try
        {
            const Field field( 2357 );
            TEST_ASSERT_EQUAL_INT( Field::green, field.getType() );

            const auto rgb = field.getColor();
            TEST_ASSERT_EQUAL_INT( 0, rgb.red );
            TEST_ASSERT_EQUAL_INT( 255, rgb.green );
            TEST_ASSERT_EQUAL_INT( 0, rgb.blue );
        }
        catch ( const std::exception& exception )
        {
            TEST_FAIL_MESSAGE( exception.what() );
        }
    }

    // Value none should have black color
    {
        try
        {
            const Field field( Field::none );
            TEST_ASSERT_EQUAL_INT( Field::none, field.getType() );

            const auto rgb = field.getColor();
            TEST_ASSERT_EQUAL_INT( 0, rgb.red );
            TEST_ASSERT_EQUAL_INT( 0, rgb.green );
            TEST_ASSERT_EQUAL_INT( 0, rgb.blue );
        }
        catch ( const std::exception& exception )
        {
            TEST_FAIL_MESSAGE( exception.what() );
        }
    }
}

void testField_getColor()
{
    static_assert( Field::red == 1540 );

    const Field field( 1400 );

    const auto rgb = field.getColor();

    TEST_ASSERT_EQUAL_INT( 255, rgb.red );
    TEST_ASSERT_EQUAL_INT( 0, rgb.green );
    TEST_ASSERT_EQUAL_INT( 0, rgb.blue );
}

void testField_upgrade()
{
    static_assert( Field::purple == 3276 );

    {
        Field field;
        const auto result = field.upgrade();
        TEST_ASSERT_FALSE( result );
        TEST_ASSERT_EQUAL( Field::black, field.getType() );
        TEST_ASSERT_EQUAL( Field::Building::levelNone, field.getBuilding() );
    }

    {
        // Full upgrade cycle

        Field field( 3276 );

        {
            const auto result = field.upgrade();
            TEST_ASSERT_TRUE( result );
            TEST_ASSERT_EQUAL( Field::purple, field.getType() );
            TEST_ASSERT_EQUAL( Field::Building::levelFirst, field.getBuilding() );
        }
        {
            const auto result = field.upgrade();
            TEST_ASSERT_TRUE( result );
            TEST_ASSERT_EQUAL( Field::purple, field.getType() );
            TEST_ASSERT_EQUAL( Field::Building::levelSecond, field.getBuilding() );
        }

        {
            const auto result = field.upgrade();
            TEST_ASSERT_TRUE( result );
            TEST_ASSERT_EQUAL( Field::purple, field.getType() );
            TEST_ASSERT_EQUAL( Field::Building::levelThird, field.getBuilding() );
        }

        {
            const auto result = field.upgrade();
            TEST_ASSERT_FALSE( result );
            TEST_ASSERT_EQUAL( Field::purple, field.getType() );
            TEST_ASSERT_EQUAL( Field::Building::levelThird, field.getBuilding() );
        }
    }
}

void testField_operatorEquals()
{
    {
        const Field fieldLeft( Field::blue );
        const Field fieldRight( Field::blue );

        TEST_ASSERT_TRUE( fieldLeft == fieldRight );

        const Field fieldAnother( Field::red );

        TEST_ASSERT_FALSE( fieldLeft == fieldAnother );
    }

    {
        const Field fieldLeft( Field::blue );
        Field fieldRight( Field::blue );

        fieldRight.upgrade();

        TEST_ASSERT_FALSE( fieldLeft == fieldRight );
    }
}
