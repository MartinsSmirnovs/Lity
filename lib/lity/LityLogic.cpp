#include "LityLogic.h"
#include "AnimationFactory.h"
#include "Converter.h"
#include "Differ.h"
#include "FigureFactory.h"
#include <stdexcept>

void LityLogic::populateFields( const FieldsRaw& rawFields )
{
    Converter::toFields( rawFields, fields );
}

auto LityLogic::process( const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight ) -> AnimationList
{
    // Get field+point from difference between two raw fields lists
    const auto& fieldPoint = makeFieldPoint( fieldsLeft, fieldsRight );

    // This is reading from pulled up pin. Skip
    const auto& field = fieldPoint.first;
    if ( field.isNone() )
    {
        return AnimationList();
    }

    const auto& figure = findFigure( fields, fieldPoint );
    if ( !figure )
    {
        return AnimationList();
    }

    return figure->apply( fields, fieldPoint );
}

const Field& LityLogic::getFieldAt( const Point& point ) const
{
    return getFields()[ point.y ][ point.x ];
}

auto LityLogic::findFigure( const Fields& fields, const FieldPoint& fieldPoint ) const -> IFigure
{
    FigureFactory figureFactory;
    IFigure figure;

    figure = figureFactory.yield();
    while ( figure )
    {
        if ( figure->find( fields, fieldPoint ) )
        {
            return figure;
        }
        figure = figureFactory.yield();
    }

    return figure;
}

FieldPoint LityLogic::makeFieldPoint( const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight ) const
{
    const auto idValuePair = Differ::diff( fieldsLeft, fieldsRight );

    const auto id = idValuePair.first;
    const auto value = idValuePair.second;

    if ( value == Differ::noDifference )
    {
        throw std::runtime_error( "No difference between raw fields values!" );
    }

    const auto& point = Converter::toFieldId( id );
    const auto& field = Field( value );

    return std::make_pair( field, point );
}

const Fields& LityLogic::getFields() const
{
    return fields;
}
