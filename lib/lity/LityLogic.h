#pragma once

#include "Figure.h"
#include "LityConfig.h"
#include <memory>

class LityLogic
{
    using IFigure = std::shared_ptr< Figure >;
    using AnimationList = Figure::AnimationList;

public:
    AnimationList process( const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight );
    void populateFields( const FieldsRaw& rawFields );

    const Fields& getFields() const;
    const Field& getFieldAt( const Point& point ) const;

private:
    Fields fields;

    FieldPoint makeFieldPoint( const FieldsRaw& fieldsLeft, const FieldsRaw& fieldsRight ) const;

    IFigure findFigure( const Fields& fields, const FieldPoint& fieldPoint ) const;
};
