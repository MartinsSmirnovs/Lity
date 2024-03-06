#pragma once

#include "Animation.h"
#include "Field.h"
#include "FigureDescription.h"
#include "LityConfig.h"
#include "Point.h"
#include <functional>
#include <vector>

class Figure
{
    using AnimationPoint = std::pair< Animation::Type, Point >;

public:
    using AnimationList = std::vector< AnimationPoint >;

    virtual bool find( const Fields& fields, const FieldPoint& fieldPoint );
    virtual AnimationList apply( Fields& fields, const FieldPoint& fieldPoint );

protected:
    using Building = Field::Building;
    FigureDescription description;

    bool checkColorMask( const Fields& fields, const FieldPoint& fieldPoint ) const;
    bool checkBuildingMask( const Fields& fields, const FieldPoint& fieldPoint ) const;
    void applyUpgradeMask( Fields& fields, const FieldPoint& fieldPoint ) const;
    void applyPaymentMask( Fields& fields, const FieldPoint& fieldPoint ) const;
    AnimationList createAnimationList( const FieldPoint& fieldPoint ) const;

    template < typename TwoDimensionalVector >
    bool checkMask( const FieldPoint& fieldPoint,
                    const TwoDimensionalVector& mask,
                    const Point& center,
                    const std::function< bool( int x, int y, typename TwoDimensionalVector::value_type::value_type maskValue ) > condition ) const
    {
        const int width = mask.front().size();
        const int height = mask.size();

        const auto& point = fieldPoint.second;
        const Point startPoint = point - center;

        for ( int y = startPoint.y; y < startPoint.y + height; y++ )
        {
            for ( int x = startPoint.x; x < startPoint.x + width; x++ )
            {
                const auto maskValue = mask[ y - startPoint.y ][ x - startPoint.x ];
                // Out of boundaries check
                if ( y < 0 || y >= sideSize || x < 0 || x >= sideSize )
                {
                    return false;
                }

                if ( !condition( x, y, maskValue ) )
                {
                    return false;
                }
            }
        }
        return true;
    }

    template < typename TwoDimensionalVector >
    void applyMask( const FieldPoint& fieldPoint,
                    const TwoDimensionalVector& mask,
                    const Point& center,
                    const std::function< void( int x, int y, typename TwoDimensionalVector::value_type::value_type maskValue ) > apply ) const
    {
        // a bit hacky reusage of checkMask which contains all required functionality
        const auto booleanApply = [ & ]( int x, int y, typename TwoDimensionalVector::value_type::value_type maskValue )
        {
            apply( x, y, maskValue );
            return true;
        };
        checkMask( fieldPoint, mask, center, booleanApply );
    }

    template < typename TwoDimensionalVector >
    bool checkBoundaries( const FieldPoint& fieldPoint, const TwoDimensionalVector& mask, const Point& center ) const
    {
        const int width = mask.front().size();
        const int height = mask.size();
        const auto& point = fieldPoint.second;

        const Point maskTopLeft( point.y - ( height - center.y - 1 ), point.x - ( width - center.x - 1 ) );
        if ( maskTopLeft.hasNegative() )
        {
            return false;
        }

        const Point maskBottomRight( point.y + ( height + center.y + 1 ), point.x + ( width + center.x + 1 ) );
        if ( maskBottomRight.hasNegative() )
        {
            return false;
        }

        return true;
    }
};
