#include "Square.h"
#include <unity.h>
#include <utility>

void testSquare_find()
{
    // No square, because all fields are empty
    {
        Fields fields;
        const Field field( Field::red );
        const Point point( 3, 2 );
        fields[ 3 ][ 3 ] = field;
        fields[ 3 ][ 3 ].upgrade();

        Square figure;
        const auto fieldPoint = std::make_pair( field, point );

        const auto result = figure.find( fields, fieldPoint );

        TEST_ASSERT_FALSE( result );
    }

    // Finishing Square by putting field in the middle
    {
        Fields fields;
        Field field( Field::red );
        const Point point( 2, 2 ); // middle
        fields[ 2 ][ 2 ] = field;
        fields[ 2 ][ 2 ].upgrade();

        Square figure;
        const auto fieldPoint = std::make_pair( field, point );

        fields[ 1 ][ 1 ] = field; // top left
        fields[ 1 ][ 2 ] = field; // top
        fields[ 1 ][ 3 ] = field; // top right
        fields[ 2 ][ 1 ] = field; // middle left

        fields[ 2 ][ 3 ] = field; // middle right
        fields[ 3 ][ 1 ] = field; // bottom left
        fields[ 3 ][ 2 ] = field; // bottom
        fields[ 3 ][ 3 ] = field; // bottom right

        const auto result = figure.find( fields, fieldPoint );
        TEST_ASSERT_TRUE( result );
    }

    // No square, because the figure was not put in the middle
    {
        Fields fields;
        const Field field( Field::red );
        const Point point( 1, 2 ); // top
        fields[ 2 ][ 2 ] = field;
        fields[ 2 ][ 2 ].upgrade();

        Square figure;
        const auto fieldPoint = std::make_pair( field, point );

        fields[ 1 ][ 1 ] = field; // top left

        fields[ 1 ][ 3 ] = field; // top right
        fields[ 2 ][ 1 ] = field; // middle left
        fields[ 2 ][ 2 ] = field; // middle
        fields[ 2 ][ 3 ] = field; // middle right
        fields[ 3 ][ 1 ] = field; // bottom left
        fields[ 3 ][ 2 ] = field; // bottom
        fields[ 3 ][ 3 ] = field; // bottom right

        const auto result = figure.find( fields, fieldPoint );
        TEST_ASSERT_FALSE( result );
    }

    // No square, because of bottom boundary
    {
        Fields fields;
        const Field field( Field::red );
        const Point point( 4, 2 ); // middle
        fields[ 4 ][ 2 ] = field;
        fields[ 4 ][ 2 ].upgrade();

        Square figure;
        const auto fieldPoint = std::make_pair( field, point );

        fields[ 3 ][ 1 ] = field; // top left
        fields[ 3 ][ 2 ] = field; // top
        fields[ 3 ][ 3 ] = field; // top right
        fields[ 4 ][ 1 ] = field; // middle left
        fields[ 4 ][ 3 ] = field; // middle right

        const auto result = figure.find( fields, fieldPoint );
        TEST_ASSERT_FALSE( result );
    }

    // No square, because of left boundary
    {
        Fields fields;
        const Field field( Field::red );
        const Point point( 2, 0 ); // middle
        fields[ 2 ][ 0 ] = field;
        fields[ 2 ][ 0 ].upgrade();

        Square figure;
        const auto fieldPoint = std::make_pair( field, point );

        fields[ 1 ][ 0 ] = field; // top
        fields[ 1 ][ 1 ] = field; // top right
        fields[ 2 ][ 1 ] = field; // middle right
        fields[ 3 ][ 0 ] = field; // bottom
        fields[ 3 ][ 1 ] = field; // bottom right

        const auto result = figure.find( fields, fieldPoint );
        TEST_ASSERT_FALSE( result );
    }

    // No square, because of building right above
    {
        Fields fields;
        const Field field( Field::red );
        const Point point( 2, 2 ); // middle
        fields[ 2 ][ 2 ] = field;
        fields[ 2 ][ 2 ].upgrade();

        Square figure;
        const auto fieldPoint = std::make_pair( field, point );

        fields[ 1 ][ 1 ] = field; // top left
        fields[ 1 ][ 2 ] = field; // top
        fields[ 1 ][ 3 ] = field; // top right
        fields[ 2 ][ 1 ] = field; // middle left

        fields[ 2 ][ 3 ] = field; // middle right
        fields[ 3 ][ 1 ] = field; // bottom left
        fields[ 3 ][ 2 ] = field; // bottom
        fields[ 3 ][ 3 ] = field; // bottom right


        fields[ 1 ][ 2 ].upgrade();

        const auto result = figure.find( fields, fieldPoint );
        TEST_ASSERT_FALSE( result );
    }

    // Finishing square with building on bottom right corner
    {
        Fields fields;
        const Field field( Field::red );
        const Point point( 2, 2 ); // middle
        fields[ 2 ][ 2 ] = field;
        fields[ 2 ][ 2 ].upgrade();

        Square figure;
        const auto fieldPoint = std::make_pair( field, point );

        fields[ 1 ][ 1 ] = field; // top left
        fields[ 1 ][ 2 ] = field; // top
        fields[ 1 ][ 3 ] = field; // top right
        fields[ 2 ][ 1 ] = field; // middle left

        fields[ 2 ][ 3 ] = field; // middle right
        fields[ 3 ][ 1 ] = field; // bottom left
        fields[ 3 ][ 2 ] = field; // bottom
        fields[ 3 ][ 3 ] = field; // bottom right

        fields[ 3 ][ 3 ].upgrade();

        const auto result = figure.find( fields, fieldPoint );
        TEST_ASSERT_TRUE( result );
    }
}

void testSquare_apply()
{
    {
        Fields fields;
        const Field field( Field::red );
        const Point point( 2, 2 ); // middle
        Square figure;
        const auto fieldPoint = std::make_pair( field, point );

        fields[ 1 ][ 1 ] = field; // top left
        fields[ 1 ][ 2 ] = field; // top
        fields[ 1 ][ 3 ] = field; // top right
        fields[ 2 ][ 1 ] = field; // middle left

        fields[ 2 ][ 3 ] = field; // middle right
        fields[ 3 ][ 1 ] = field; // bottom left
        fields[ 3 ][ 2 ] = field; // bottom
        fields[ 3 ][ 3 ] = field; // bottom right

        const auto animationList = figure.apply( fields, fieldPoint );

        TEST_ASSERT_EQUAL( Field::Type::red, fields[ 1 ][ 1 ].getType() );
        TEST_ASSERT_EQUAL( Field::Type::black, fields[ 1 ][ 2 ].getType() );
        TEST_ASSERT_EQUAL( Field::Type::red, fields[ 1 ][ 3 ].getType() );
        TEST_ASSERT_EQUAL( Field::Type::black, fields[ 2 ][ 1 ].getType() );
        TEST_ASSERT_EQUAL( Field::Type::red, fields[ 2 ][ 2 ].getType() );
        TEST_ASSERT_EQUAL( Field::Type::black, fields[ 2 ][ 3 ].getType() );
        TEST_ASSERT_EQUAL( Field::Type::red, fields[ 3 ][ 1 ].getType() );
        TEST_ASSERT_EQUAL( Field::Type::black, fields[ 3 ][ 2 ].getType() );
        TEST_ASSERT_EQUAL( Field::Type::red, fields[ 3 ][ 3 ].getType() );

        TEST_ASSERT_EQUAL( Field::Building::levelFirst, fields[ 2 ][ 2 ].getBuilding() );

        TEST_ASSERT_EQUAL( Animation::payment, animationList[ 0 ].first );
        TEST_ASSERT_EQUAL( Animation::payment, animationList[ 1 ].first );
        TEST_ASSERT_EQUAL( Animation::appearance, animationList[ 2 ].first );
        TEST_ASSERT_EQUAL( Animation::payment, animationList[ 3 ].first );
        TEST_ASSERT_EQUAL( Animation::payment, animationList[ 4 ].first );

        TEST_ASSERT_TRUE( Point( 1, 2 ) == animationList[ 0 ].second );
        TEST_ASSERT_TRUE( Point( 2, 1 ) == animationList[ 1 ].second );
        TEST_ASSERT_TRUE( Point( 2, 2 ) == animationList[ 2 ].second );
        TEST_ASSERT_TRUE( Point( 2, 3 ) == animationList[ 3 ].second );
        TEST_ASSERT_TRUE( Point( 3, 2 ) == animationList[ 4 ].second );
    }
}
