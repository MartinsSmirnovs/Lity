#include "IdleReader.h"
#include "LityConfig.h"
#include <Arduino.h>
#include <array>

namespace IdleReader
{
// An arbitrary threshold which can be counted as a valid reading
// 4095 is the max value that analogRead can return
constexpr static int threshold = 4095 - 5;

// Actual count of reading pins on the game board
constexpr static int analogPins = 60;
using RawReadings = std::array< uint16_t, analogPins >;

// How many pins per each analog demultiplexer chip
constexpr static int analogPinsPerChip = 8;

// Contains pairs of pin number and it's position for analog demultiplexer
static const std::vector< std::pair< gpio_num_t, uint8_t > > dataSelectPairs = {
    { GPIO_NUM_23, 0x1 },
    { GPIO_NUM_22, 0x2 },
    { GPIO_NUM_21, 0x4 }
};

// Pins from which data reading is happening.
// Note that the order of pins here is very important, because we later perform special kind of sorting
// assuming that each of the pins in this list come one after another
static const std::vector< gpio_num_t > commonInPins = {
    GPIO_NUM_34, GPIO_NUM_35,
    GPIO_NUM_32, GPIO_NUM_33,
    GPIO_NUM_25, GPIO_NUM_26,
    GPIO_NUM_27, GPIO_NUM_14
};

static const std::array< std::pair< int, int >, fieldsCount > fieldDefinitions = {
    {
    { 0, 0 }, // 00
    { 0, 0 }, // 01
    { 0, 0 }, // 02
    { 0, 0 }, // 03
    { 0, 0 }, // 04
    { 0, 0 }, // 05
    { 0, 0 }, // 06
    { 0, 0 }, // 07
    { 0, 0 }, // 08
    { 0, 0 }, // 09
    { 0, 0 }, // 10
    { 0, 0 }, // 11
    { 0, 0 }, // 12
    { 0, 0 }, // 13
    { 0, 0 }, // 14
    { 0, 0 }, // 15
    { 0, 0 }, // 16
    { 0, 0 }, // 17
    { 0, 0 }, // 18
    { 0, 0 }, // 19
    { 0, 0 }, // 20
    { 0, 0 }, // 21
    { 0, 0 }, // 22
    { 0, 0 }, // 23
    { 0, 0 }, // 24
    { 0, 0 }, // 25
    { 0, 0 }, // 26
    { 0, 0 }, // 27
    { 0, 0 }, // 28
    { 0, 0 }, // 29
    { 0, 0 }, // 30
    { 0, 0 }, // 31
    { 0, 0 }, // 32
    { 0, 0 }, // 33
    { 0, 0 }, // 34
    { 0, 0 }, // 35
    { 0, 0 }, // 36
    { 0, 0 }, // 37
    { 0, 0 }, // 38
    { 0, 0 }, // 39
    { 0, 0 }, // 40
    { 0, 0 }, // 41
    { 0, 0 }, // 42
    { 0, 0 }, // 43
    { 0, 0 }, // 44
    { 0, 0 }, // 45
    { 0, 0 }, // 46
    { 0, 0 }, // 47
    { 0, 0 }, // 48
    { 0, 0 }, // 49

    { 10, 22 }, // 50
    { 9, 22 },  // 51
    { 9, 23 },  // 52
    { 8, 23 },  // 53
    { 8, 21 },  // 54
    { 42, 21 }, // 55
    { 42, 54 }, // 56
    { 55, 54 }, // 57
    { 55, 53 }, // 58
    { 43, 53 }, // 59

    { 22, 20 }, // 60
    { 22, 18 }, // 61
    { 23, 18 }, // 62
    { 23, 19 }, // 63
    { 21, 19 }, // 64
    { 21, 52 }, // 65
    { 54, 52 }, // 66
    { 54, 51 }, // 67
    { 53, 51 }, // 68
    { 53, 48 }, // 69

    { 20, 17 }, // 70
    { 18, 17 }, // 71
    { 18, 16 }, // 72
    { 19, 16 }, // 73
    { 19, 50 }, // 74
    { 52, 50 }, // 75
    { 52, 49 }, // 76
    { 51, 49 }, // 77
    { 0, 0 },   // 78 ???????????????????????
    { 0, 0 },   // 79 ???????????????????????

    { 28, 17 }, // 80
    { 30, 17 }, // 81
    { 30, 16 }, // 82
    { 31, 16 }, // 83
    { 31, 50 }, // 84
    { 29, 50 }, // 85
    { 29, 49 }, // 86
    { 0, 0 },   // 87 ???????????????????????
    { 0, 0 },   // 88 ???????????????????????
    { 0, 0 },   // 89 ???????????????????????


    { 28, 26 }, // 90
    { 30, 26 }, // 91
    { 30, 25 }, // 92
    { 31, 25 }, // 93
    { 31, 27 }, // 94
    { 29, 27 }, // 95
    { 29, 24 }, // 96
    { 0, 0 },   // 97 ???????????????????????
    { 0, 0 },   // 98 ???????????????????????
    { 0, 0 },   // 99 ???????????????????????
    }
};

void rawDebouncedRead( RawReadings& );
void sort( RawReadings& );
void convert( RawReadings&, FieldsRaw& );

void setup()
{
    for ( const auto& pin : commonInPins )
    {
        pinMode( pin, INPUT );
    }

    for ( const auto& pair : dataSelectPairs )
    {
        pinMode( pair.first, OUTPUT );
    }
}

void rawRead( RawReadings& readings )
{
    // Serial.println( "Raw read" );
    const auto commonInPinsCount = commonInPins.size();

    int counter = 0;

    for ( int i = 0; i < commonInPinsCount; i++ )
    {
        for ( uint8_t j = 0; j < analogPinsPerChip; j++ )
        {
            for ( const auto& pair : dataSelectPairs )
            {
                digitalWrite( pair.first, j & pair.second );
            }

            if ( counter < readings.size() )
            {
                readings[ counter ] = std::min( analogRead( commonInPins[ i ] ), readings[ counter ] );
            }
            else
            {
                // for ( int i = 0; i < 60; i += 2 )
                // {
                //     char buffer[ 22 ] = {};
                //     snprintf( buffer, 22, "%2d: %4d %2d: %4d ", i, readings[ i ], i + 1, readings[ i + 1 ] );
                //     Serial.println( buffer );
                // }
                // Serial.println( "--------------------------" );
                // delay( 2000 );

                return;
            }
            counter++;
        }
    }
}

void rawDebouncedRead( RawReadings& readings )
{
    constexpr static int maxCount = 10;

    std::array< int, std::tuple_size< RawReadings >{} > debounceCounter;

    int stableReadingCount = 0;
    auto debounceEndTime = 0;

    while ( true )
    {
        rawRead( readings );

        for ( int i = 0; i < readings.size(); i++ )
        {
            // We got a valid reading
            if ( readings[ i ] <= threshold )
            {
                debounceCounter[ i ]++;

                // If debouncing just started
                if ( debounceEndTime == 0 )
                {
                    Serial.println( "Debounce started" );
                    constexpr int debounceTimeMillis = 400;
                    debounceEndTime = millis() + debounceTimeMillis;
                }
            }

            if ( debounceCounter[ i ] == maxCount )
            {
                stableReadingCount++;
            }
        }

        // If we got 2 stable reads, debouncing succeeded
        if ( stableReadingCount >= 2 )
        {
            Serial.println( "Debounce ended" );
            return;
        }

        // If debounce time passed and we are still here it means that debouncing failed
        if ( millis() >= debounceEndTime )
        {
            debounceEndTime = 0;
            stableReadingCount = 0;
            debounceCounter = {};
            readings.fill( 4095 );
        }
    }
}

void read( FieldsRaw& fields )
{
    RawReadings readings;
    readings.fill( 4095 );

    rawDebouncedRead( readings );

    convert( readings, fields );
}

void readUndebounced( FieldsRaw& fields )
{
    RawReadings readings;
    readings.fill( 4095 );

    rawRead( readings );

    convert( readings, fields );
}

void convert( RawReadings& readings, FieldsRaw& fields )
{
    static_assert( std::tuple_size< decltype( fieldDefinitions ) >{} == std::tuple_size< FieldsRaw >{}, "" );

    // for ( int a = 0; a < 10; a++ )
    // {
    //     for ( int b = 0; b < 6; b++ )
    //     {
    //         Serial.print( a * 6 + b );
    //         Serial.print( ": " );
    //         Serial.print( readings[ a * 6 + b ] );
    //         Serial.print( "    " );
    //     }
    //     Serial.println();
    // }

    for ( int i = 0; i < fieldDefinitions.size(); i++ )
    {
        const auto& pinA = fieldDefinitions[ i ].first;
        const auto& pinB = fieldDefinitions[ i ].second;

        if ( readings[ pinA ] <= threshold && readings[ pinB ] <= threshold )
        {
            fields[ i ] = std::min( readings[ pinA ], readings[ pinB ] );
        }
        else
        {
            fields[ i ] = std::max( readings[ pinA ], readings[ pinB ] );
        }
    }
}

} // namespace IdleReader
