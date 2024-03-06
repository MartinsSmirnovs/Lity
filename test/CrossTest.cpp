#include "Cross.h"
#include <unity.h>
#include <utility>

void testCross_find()
{
    // No cross, because all fields are empty
    {
        const Fields fields;
        const Field field( Field::red );
        const Point point( 3, 2 );
        Cross figure;
        const auto fieldPoint = std::make_pair( field, point );

        const auto result = figure.find( fields, fieldPoint );

        TEST_ASSERT_FALSE( result );
    }

    // Finishing cross by putting field in the middle
    {
        Fields fields;
        const Field field( Field::red );
        const Point point( 3, 2 ); // middle
        Cross figure;
        const auto fieldPoint = std::make_pair( field, point );

        fields[ 4 ][ 2 ] = field; // bottom
        fields[ 2 ][ 2 ] = field; // top
        fields[ 3 ][ 3 ] = field; // right
        fields[ 3 ][ 1 ] = field; // left

        const auto result = figure.find( fields, fieldPoint );
        TEST_ASSERT_TRUE( result );
    }

    // No cross, because the figure was not put in the middle
    {
        Fields fields;
        const Field field( Field::red );
        const Point point( 4, 2 ); // bottom
        Cross figure;
        const auto fieldPoint = std::make_pair( field, point );

        fields[ 3 ][ 2 ] = field; // middle
        fields[ 2 ][ 2 ] = field; // top
        fields[ 3 ][ 3 ] = field; // right
        fields[ 3 ][ 1 ] = field; // left

        const auto result = figure.find( fields, fieldPoint );
        TEST_ASSERT_FALSE( result );
    }

    // No cross, because of top boundary
    {
        Fields fields;
        const Field field( Field::red );
        const Point point( 0, 2 ); // middle
        Cross figure;
        const auto fieldPoint = std::make_pair( field, point );

        fields[ 1 ][ 2 ] = field; // bottom

        fields[ 0 ][ 3 ] = field; // right
        fields[ 0 ][ 1 ] = field; // left

        const auto result = figure.find( fields, fieldPoint );
        TEST_ASSERT_FALSE( result );
    }

    // No cross, because of right boundary
    {
        Fields fields;
        const Field field( Field::red );
        const Point point( 1, 4 ); // middle
        Cross figure;
        const auto fieldPoint = std::make_pair( field, point );

        fields[ 0 ][ 4 ] = field; // top
        fields[ 2 ][ 4 ] = field; // bottom

        fields[ 1 ][ 3 ] = field; // left

        const auto result = figure.find( fields, fieldPoint );
        TEST_ASSERT_FALSE( result );
    }

    // No cross, because of building right below
    {
        Fields fields;
        const Field field( Field::red );
        const Point point( 3, 2 ); // middle
        Cross figure;
        const auto fieldPoint = std::make_pair( field, point );

        fields[ 4 ][ 2 ] = field; // bottom
        fields[ 2 ][ 2 ] = field; // top
        fields[ 3 ][ 3 ] = field; // right
        fields[ 3 ][ 1 ] = field; // left

        fields[ 4 ][ 2 ].upgrade();

        const auto result = figure.find( fields, fieldPoint );
        TEST_ASSERT_FALSE( result );
    }

    // Finishing cross with buildings on top right and bottom left corners
    {
        Fields fields;
        const Field field( Field::red );
        const Point point( 3, 2 ); // middle
        Cross figure;
        const auto fieldPoint = std::make_pair( field, point );

        fields[ 4 ][ 2 ] = field; // bottom
        fields[ 2 ][ 2 ] = field; // top
        fields[ 3 ][ 3 ] = field; // right
        fields[ 3 ][ 1 ] = field; // left

        fields[ 2 ][ 3 ].upgrade();
        fields[ 4 ][ 1 ].upgrade();

        const auto result = figure.find( fields, fieldPoint );
        TEST_ASSERT_TRUE( result );
    }
}

void testCross_apply()
{
    {
        Fields fields;
        const Field field( Field::red );
        const Point point( 3, 2 ); // middle
        Cross figure;
        const auto fieldPoint = std::make_pair( field, point );

        fields[ 4 ][ 2 ] = field; // bottom
        fields[ 2 ][ 2 ] = field; // top
        fields[ 3 ][ 3 ] = field; // right
        fields[ 3 ][ 1 ] = field; // left

        const auto animationList = figure.apply( fields, fieldPoint );

        TEST_ASSERT_EQUAL( Field::Type::black, fields[ 4 ][ 2 ].getType() );
        TEST_ASSERT_EQUAL( Field::Type::black, fields[ 2 ][ 2 ].getType() );
        TEST_ASSERT_EQUAL( Field::Type::black, fields[ 3 ][ 3 ].getType() );
        TEST_ASSERT_EQUAL( Field::Type::black, fields[ 3 ][ 1 ].getType() );
        TEST_ASSERT_EQUAL( Field::Type::red, fields[ 3 ][ 2 ].getType() );

        TEST_ASSERT_EQUAL( Field::Building::levelFirst, fields[ 3 ][ 2 ].getBuilding() );

        TEST_ASSERT_EQUAL( Animation::payment, animationList[ 0 ].first );
        TEST_ASSERT_EQUAL( Animation::payment, animationList[ 1 ].first );
        TEST_ASSERT_EQUAL( Animation::appearance, animationList[ 2 ].first );
        TEST_ASSERT_EQUAL( Animation::payment, animationList[ 3 ].first );
        TEST_ASSERT_EQUAL( Animation::payment, animationList[ 4 ].first );

        TEST_ASSERT_TRUE( Point( 2, 2 ) == animationList[ 0 ].second );
        TEST_ASSERT_TRUE( Point( 3, 1 ) == animationList[ 1 ].second );
        TEST_ASSERT_TRUE( Point( 3, 2 ) == animationList[ 2 ].second );
        TEST_ASSERT_TRUE( Point( 3, 3 ) == animationList[ 3 ].second );
        TEST_ASSERT_TRUE( Point( 4, 2 ) == animationList[ 4 ].second );
    }
}
