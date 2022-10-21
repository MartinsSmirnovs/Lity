#include "Converter.h"
#include "LityConfig.h"

void Converter::toFields(const FieldsRaw& rawFields, Fields& fields) {
    fields[0][0] = rawFields[0];
    fields[0][1] = rawFields[5];
    fields[0][2] = rawFields[10];
    fields[0][3] = rawFields[14];
    fields[0][4] = rawFields[20];

    fields[1][0] = rawFields[1];
    fields[1][1] = rawFields[6];
    fields[1][2] = rawFields[11];
    fields[1][3] = rawFields[16];
    fields[1][4] = rawFields[21];

    fields[2][0] = rawFields[2];
    fields[2][1] = rawFields[7];
    fields[2][2] = rawFields[12];
    fields[2][3] = rawFields[19];
    fields[2][4] = rawFields[22];

    fields[3][0] = rawFields[3];
    fields[3][1] = rawFields[8];
    fields[3][2] = rawFields[13];
    fields[3][3] = rawFields[17];
    fields[3][4] = rawFields[23];

    fields[4][0] = rawFields[4];
    fields[4][1] = rawFields[9];
    fields[4][2] = rawFields[15];
    fields[4][3] = rawFields[18];
    fields[4][4] = rawFields[24];
}

int Converter::toId(const Coord& coord, int rows) {
    return coord.y * rows + coord.x;
}

int Converter::toStripId(int id) {
    int result = 0;
    switch (id) {
        case 0:
            return 4;
            break;
        case 1:
            return 5;
            break;
        case 2:
            return 14;
            break;
        case 3:
            return 15;
            break;
        case 4:
            return 24;
            break;
        case 5:
            return 3;
            break;
        case 6:
            return 6;
            break;
        case 7:
            return 13;
            break;
        case 8:
            return 16;
            break;
        case 9:
            return 23;
            break;
        case 10:
            return 2;
            break;
        case 11:
            return 7;
            break;
        case 12:
            return 12;
            break;
        case 13:
            return 17;
            break;
        case 14:
            return 22;
            break;
        case 15:
            return 1;
            break;
        case 16:
            return 8;
            break;
        case 17:
            return 11;
            break;
        case 18:
            return 18;
            break;
        case 19:
            return 21;
            break;
        case 20:
            return 0;
            break;
        case 21:
            return 9;
            break;
        case 22:
            return 10;
            break;
        case 23:
            return 19;
            break;
        case 24:
            return 20;
            break;
        default:
            return -1;
            break;
    }
}