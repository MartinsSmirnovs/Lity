#include "FigureDescription.h"
#include <algorithm>
#include <functional>

void FigureDescription::flip( Direction direction )
{
    Axis axis;

    switch ( direction )
    {
        case Direction::top:
        {
            // By default, description is already pointed to top
            return;
        }
        break;
        case Direction::left:
        {
            axis = Axis::x;
        }
        break;
        case Direction::right:
        {
            axis = Axis::y;
        }
        break;
        case Direction::bottom:
        {
            axis = Axis::both;
        }
        break;
    };

    if ( axis == Axis::both )
    {
        flip( Axis::y );
        flip( Axis::x );
    }
    else
    {
        flip( axis );
    }
}

void FigureDescription::flip( Axis axis )
{
    flip( colorMask, center, axis );
    flip( paymentMask, center, axis );
    flip( buildingMask, center, axis );
    flip( upgradeMask, center, axis );
    flip( animationMask, center, axis );
}

template < typename TwoDimensionalVector >
void FigureDescription::flip( TwoDimensionalVector& mask, Point& point, Axis axis )
{
    int rowCount = mask.size();
    int columnCount = mask[ 0 ].size();

    int rowIterations = 0;
    int columnIterations = 0;

    std::function< Point( int i, int j ) > getMirrorPosition;

    if ( axis == Axis::x )
    {
        rowIterations = rowCount / 2;
        columnIterations = columnCount;
        getMirrorPosition = [ & ]( int i, int j )
        {
            return Point( rowCount - i - 1, j );
        };
    }

    if ( axis == Axis::y )
    {
        rowIterations = rowCount;
        columnIterations = columnCount / 2;
        getMirrorPosition = [ & ]( int i, int j )
        {
            return Point( i, columnCount - j - 1 );
        };
    }

    for ( int i = 0; i < rowIterations; i++ )
    {
        for ( int j = 0; j < columnIterations; j++ )
        {
            const auto& mirrorPosition = getMirrorPosition( i, j );

            std::swap( mask[ i ][ j ], mask[ mirrorPosition.y ][ mirrorPosition.x ] );

            const auto currentPosition = Point( i, j );
            if ( point == currentPosition )
            {
                point = mirrorPosition;
            }
            else if ( point == mirrorPosition )
            {
                point = currentPosition;
            }
        }
    }
}

template void FigureDescription::flip( std::vector< std::vector< Field::Type > >& mask, Point& point, Axis axis );
template void FigureDescription::flip( std::vector< std::vector< Building > >& mask, Point& point, Axis axis );
template void FigureDescription::flip( std::vector< std::vector< bool > >& mask, Point& point, Axis axis );
