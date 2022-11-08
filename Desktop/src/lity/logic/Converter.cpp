#include "Converter.h"
#include "LityConfig.h"

Point Converter::toFieldId(int rawId) {
    const int y = rawId / sideSize;
    const int x = rawId % sideSize;
    return Point(y, x);
}

void Converter::toFields(const FieldsRaw& rawFields, Fields& fields) {
    fields[0][0] = Field(rawFields[0]);
    fields[0][1] = Field(rawFields[5]);
    fields[0][2] = Field(rawFields[10]);
    fields[0][3] = Field(rawFields[14]);
    fields[0][4] = Field(rawFields[20]);

    fields[1][0] = Field(rawFields[1]);
    fields[1][1] = Field(rawFields[6]);
    fields[1][2] = Field(rawFields[11]);
    fields[1][3] = Field(rawFields[16]);
    fields[1][4] = Field(rawFields[21]);

    fields[2][0] = Field(rawFields[2]);
    fields[2][1] = Field(rawFields[7]);
    fields[2][2] = Field(rawFields[12]);
    fields[2][3] = Field(rawFields[19]);
    fields[2][4] = Field(rawFields[22]);

    fields[3][0] = Field(rawFields[3]);
    fields[3][1] = Field(rawFields[8]);
    fields[3][2] = Field(rawFields[13]);
    fields[3][3] = Field(rawFields[17]);
    fields[3][4] = Field(rawFields[23]);

    fields[4][0] = Field(rawFields[4]);
    fields[4][1] = Field(rawFields[9]);
    fields[4][2] = Field(rawFields[15]);
    fields[4][3] = Field(rawFields[18]);
    fields[4][4] = Field(rawFields[24]);
}

int Converter::toId(const Point& point, int rows) {
    return point.y * rows + point.x;
}

int Converter::toStripId(int id) {
    return id;
}
