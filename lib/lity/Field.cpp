#ifndef BUILD_ESP32
#include <string>
#endif
#include "Field.h"
#include <stdexcept>

const std::vector< Field::Type > Field::typeList = {
    white,
    blue,
    red,
    green,
    purple,
    black,
    none
};

const std::map< Field::Type, RGB > Field::typeColorMap = {
    { black, { 0, 0, 0 } },
    { white, { 255, 255, 255 } },
    { blue, { 0, 0, 255 } },
    { red, { 255, 0, 0 } },
    { green, { 0, 255, 0 } },
    { purple, { 255, 0, 255 } }
};

Field::Field( uint16_t value )
{
    const auto targetIterator = closest( typeList, value );

    if ( targetIterator == typeList.end() )
    {
        throw std::invalid_argument( "Lower bound for value " + std::to_string( value ) + " could not be found!" );
    }

    const auto target = *targetIterator;

    if ( !inRange( target, value ) )
    {
        throw std::out_of_range( "Value " + std::to_string( value ) + " is out of range!" );
    }

    type = target;
}

bool Field::inRange( Type target, int value )
{
    // Value too small
    if ( target - digitalRange > value )
    {
        return false;
    }

    // Value too big
    if ( target + digitalRange < value )
    {
        return false;
    }
    return true;
}

void Field::setType( Type type )
{
    this->type = type;
}

const RGB& Field::getColor() const
{
    return getColor( type );
}

const RGB& Field::getColor( Type type )
{
    if ( type == none )
    {
        return typeColorMap.at( black );
    }

    return typeColorMap.at( type );
}

auto Field::getType() const -> Type
{
    return type;
}

auto Field::getBuilding() const -> Building
{
    return building;
}

auto Field::closest( const TypeList& list, int value ) -> TypeList::const_iterator
{
    const auto lowerBoundIterator = std::lower_bound( list.begin(),
                                                      list.end(),
                                                      value );

    if ( lowerBoundIterator == list.end() )
    {
        return lowerBoundIterator;
    }

    int previousValue = 0;
    if ( lowerBoundIterator != list.begin() )
    {
        previousValue = *( lowerBoundIterator - 1 );
    }
    else
    {
        previousValue = *( lowerBoundIterator );
    }

    const int currentValue = *lowerBoundIterator;

    if ( abs( value - previousValue ) < abs( value - currentValue ) )
    {
        return lowerBoundIterator - 1;
    }

    return lowerBoundIterator;
}

bool Field::upgrade()
{
    if ( type == Type::white )
    {
        return false;
    }

    if ( type == Type::black )
    {
        return false;
    }

    switch ( building )
    {
        case Building::levelNone:
            building = Building::levelFirst;
            return true;
        case Building::levelFirst:
            building = Building::levelSecond;
            return true;
        case Building::levelSecond:
            building = Building::levelThird;
            return true;
        default:
            return false;
    }
}

bool Field::operator==( const Field& first ) const
{
    return type == first.type && building == first.building;
}

bool Field::isNone() const
{
    if ( type == none )
    {
        return true;
    }
    return false;
}
