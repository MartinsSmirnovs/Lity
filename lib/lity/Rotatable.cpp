#include "Rotatable.h"
#include "ScopedBackup.h"

auto Rotatable::apply( Fields& fields, const FieldPoint& fieldPoint ) -> AnimationList
{
    description.flip( foundDirection );
    return Figure::apply( fields, fieldPoint );
}

bool Rotatable::find( const Fields& fields, const FieldPoint& fieldPoint )
{
    searchByRotation( Direction::top, fields, fieldPoint );
    searchByRotation( Direction::left, fields, fieldPoint );
    searchByRotation( Direction::right, fields, fieldPoint );
    searchByRotation( Direction::bottom, fields, fieldPoint );

    return onlyOneFound;
}

void Rotatable::searchByRotation( Direction direction, const Fields& fields, const FieldPoint& fieldPoint )
{
    // Preserve original description, so all of them get rotated relative to same point
    const ScopedBackup< FigureDescription > descriptionBackup( description );

    description.flip( direction );
    const bool found = Figure::find( fields, fieldPoint );

    // If matched for more than one rotation
    if ( found && onlyOneFound )
    {
        onlyOneFound = false;
        return;
    }

    if ( found )
    {
        onlyOneFound = true;
        foundDirection = direction;
    }
}