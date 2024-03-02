#include "Blink.h"
#include "Fade.h"
#include <unity.h>

void testFade_Update()
{
    static_assert( Animation::appearance == 250 );

    // Fade goes down
    const RGB red( 255, 0, 0 );
    const RGB black;

    Fade fade( red, black, Point() );

    constexpr int timePointOfReference = 100;

    // Performs setup
    TEST_ASSERT_TRUE( fade.update( timePointOfReference ) );

    fade.update( timePointOfReference + 50 );
    fade.update( timePointOfReference + 100 );

    // Check if the value is still falling
    TEST_ASSERT_TRUE( fade.update( timePointOfReference + 200 ) );

    {
        const auto& color = fade.getColor();

        TEST_ASSERT_EQUAL_INT( 24, color.red );
        TEST_ASSERT_EQUAL_INT( 0, color.green );
        TEST_ASSERT_EQUAL_INT( 0, color.blue );
    }

    // Fade should drop to it's lowest value here
    TEST_ASSERT_TRUE( fade.update( timePointOfReference + Animation::appearance ) );

    // Fade should stop dropping after getting to it's lowest value
    TEST_ASSERT_FALSE( fade.update( timePointOfReference + Animation::appearance + 30 ) );

    {
        const auto& color = fade.getColor();

        TEST_ASSERT_EQUAL_INT( 0, color.red );
        TEST_ASSERT_EQUAL_INT( 0, color.green );
        TEST_ASSERT_EQUAL_INT( 0, color.blue );
    }
}

void testBlink_Update()
{
    static_assert( Animation::payment == 300 );

    const RGB turquoise( 0, 255, 255 );
    const RGB black;

    Blink blink( turquoise, black, Point() );

    TEST_ASSERT_TRUE( blink.update( 300 ) );

    {
        const auto& color = blink.getColor();

        TEST_ASSERT_EQUAL_INT( 0, color.red );
        TEST_ASSERT_EQUAL_INT( 0, color.green );
        TEST_ASSERT_EQUAL_INT( 0, color.blue );
    }

    TEST_ASSERT_TRUE( blink.update( 600 ) );

    {
        const auto& color = blink.getColor();

        TEST_ASSERT_EQUAL_INT( 0, color.red );
        TEST_ASSERT_EQUAL_INT( 255, color.green );
        TEST_ASSERT_EQUAL_INT( 255, color.blue );
    }

    TEST_ASSERT_TRUE( blink.update( 900 ) );
    TEST_ASSERT_TRUE( blink.update( 1200 ) );
    TEST_ASSERT_TRUE( blink.update( 1500 ) );

    TEST_ASSERT_FALSE( blink.update( 1800 ) );

    {
        const auto& color = blink.getColor();

        TEST_ASSERT_EQUAL_INT( 0, color.red );
        TEST_ASSERT_EQUAL_INT( 0, color.green );
        TEST_ASSERT_EQUAL_INT( 0, color.blue );
    }
}
