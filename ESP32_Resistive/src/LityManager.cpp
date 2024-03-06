#include "LityManager.h"
#include "AnimationFactory.h"
#include "Converter.h"
#include "Differ.h"
#include "IdleReader.h"
#include "PixelDriver.h"
#include <Arduino.h>

static int toId( const Point& point );
const Field& getFieldAt( const Point& point, const Fields& fields );

void LityManager::setup()
{
    Serial.begin( 115200 );
    PixelDriver::setup();
    IdleReader::setup();

    bool unfilled = true;
    do
    {
        // Initial reading and converting which is required for first time diff search
        IdleReader::readUndebounced( rawFieldsPrevious );

        try
        {
            logic.populateFields( rawFieldsPrevious );
            fields = logic.getFields();
            unfilled = false;
        }
        catch ( std::exception& exception )
        {
            Serial.println( exception.what() );
        }
    }
    while ( unfilled );
}

void LityManager::run()
{
    IdleReader::read( rawFields );

    // Return if there is no diff between readings
    if ( Differ::equal( rawFieldsPrevious, rawFields ) )
    {
        return;
    }

    try
    {
        const auto& animations = logic.process( rawFieldsPrevious, rawFields );
        const auto& fieldsTarget = logic.getFields();

        doAnimations( fieldsTarget, animations );

        fields = fieldsTarget;
    }
    catch ( std::exception& exception )
    {
        Serial.println( exception.what() );
    }

    updatePreviousFields();
}

void LityManager::doAnimations( const Fields& fieldsTarget, const Figure::AnimationList& animationList )
{
    std::vector< std::shared_ptr< Animation > > animations;

    for ( const auto& animationPoint : animationList )
    {
        const auto& type = animationPoint.first;
        const auto& point = animationPoint.second;
        const auto& fieldCurrent = getFieldAt( point, fields );
        const auto& fieldTarget = getFieldAt( point, fieldsTarget );

        const auto& animation = AnimationFactory::Create( fieldCurrent, fieldTarget, point, type );

        if ( !animation )
        {
            continue;
        }

        animations.push_back( std::move( animation ) );
    }

    while ( animations.size() )
    {
        for ( int i = 0; i < animations.size(); i++ )
        {
            auto& animation = animations[ i ];

            const bool updated = animation->update( millis() );

            if ( !updated )
            {
                animations.erase( animations.begin() + i );
                i--;
                continue;
            }

            const auto& color = animation->getColor();
            const auto& point = animation->getPoint();

            PixelDriver::setColor( toId( point ), color );
        }

        PixelDriver::show();
    }
}

void LityManager::updatePreviousFields()
{
    rawFieldsPrevious = rawFields;
}

int toId( const Point& point )
{
    return Converter::toId( point, sideSize );
}

const Field& getFieldAt( const Point& point, const Fields& fields )
{
    return fields[ point.y ][ point.x ];
}
