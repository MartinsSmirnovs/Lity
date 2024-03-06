#include "Converter.h"
#include "LityConfig.h"

namespace Converter
{

Point toFieldId( int rawId )
{
    const int y = rawId / sideSize;
    const int x = rawId % sideSize;
    return Point( y, x );
}

void toFields( const FieldsRaw& rawFields, Fields& fields )
{
    for ( int i = 0; i < sideSize; i++ )
    {
        for ( int j = 0; j < sideSize; j++ )
        {
            fields[ i ][ j ] = Field( rawFields[ sideSize * i + j ] );
        }
    }
}

int toId( const Point& point, int rows )
{
    return point.y * rows + point.x;
}

} // namespace Converter