#include "Point.h"

Point::Point( int y, int x )
: y( y ),
  x( x )
{
}

bool Point::isEmpty() const
{
    return x == empty && y == empty;
}

bool Point::hasNegative() const
{
    return x < 0 || y < 0;
}

Point Point::operator+( const Point& first ) const
{
    return Point( y + first.y, x + first.x );
}

Point Point::operator-( const Point& first ) const
{
    return Point( y - first.y, x - first.x );
}

bool Point::operator==( const Point& first ) const
{
    return y == first.y && x == first.x;
}

bool Point::operator!=( const Point& first ) const
{
    return !( *this == first );
}
