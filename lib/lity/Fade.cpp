#ifdef BUILD_ESP32
#include <cmath>
#else
#define _USE_MATH_DEFINES
#include <math.h>
#endif

#include "Fade.h"
#include <limits>

Fade::Fade( const RGB& colorCurrent, const RGB& colorTarget, const Point& point )
: Animation( colorCurrent, colorTarget, point )
{
}

bool Fade::update( unsigned long timeCurrent )
{
    // First time setup
    if ( firstTime )
    {
        setup();

        timeInitial = timeCurrent;
        firstTime = false;

        return true;
    }

    // If target color is reached, cannot update anymore
    if ( colorCurrent == colorTarget )
    {
        return false;
    }

    for ( int i = 0; i < colorTargetList.size(); i++ )
    {
        const auto target = colorTargetList[ i ];
        auto& color = colorDirectionList[ i ].first;
        auto& direction = colorDirectionList[ i ].second;
        auto& previous = colorPreviousList[ i ];

        if ( direction == stop )
        {
            continue;
        }

        const auto time = timeCurrent - timeInitial;
        const auto result = calculate( time, direction );

        if ( direction == down && previous < result )
        {
            color = target;
            direction = stop;
            continue;
        }

        if ( direction == up && previous > result )
        {
            color = target;
            direction = stop;
            continue;
        }

        previous = color;
        color = result;
    }

    return true;
}

void Fade::setup()
{
    // Decide which direction each color of RGB will go
    for ( int i = 0; i < colorDirectionList.size(); i++ )
    {
        const uint8_t color = colorDirectionList[ i ].first;
        const uint8_t colorTarget = colorTargetList[ i ];

        if ( color > colorTarget )
        {
            colorDirectionList[ i ].second = down;
        }
        else if ( color < colorTarget )
        {
            colorDirectionList[ i ].second = up;
        }
        else
        {
            colorDirectionList[ i ].second = stop;
        }
    }
}

uint8_t Fade::calculate( int time, Direction direction ) const
{
    constexpr float yOffset = std::numeric_limits< uint8_t >::max() / 2.0f;
    constexpr float amplitude = std::numeric_limits< uint8_t >::max() / 2.0f;

    constexpr auto pi = M_PI;

    constexpr float range = Animation::appearance;

#ifdef BUILD_ESP32
    using namespace std;
#endif
    const uint8_t result = yOffset + amplitude * cos( pi / range * time + pi * direction );

    return result;
}