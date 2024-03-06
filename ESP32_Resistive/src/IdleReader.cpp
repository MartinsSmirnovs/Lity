#include "IdleReader.h"
#include "LityConfig.h"
#include "Waiter.h"
#include <Arduino.h>
#include <algorithm>
#include <array>

namespace IdleReader
{
// 4095 is the max value that analogRead can return
constexpr static int maxValue = 4095;
// An arbitrary threshold which can be counted as a valid reading
constexpr static int threshold = maxValue - 5;

// Actual count of reading pins on the game board
constexpr static int analogPins = 60;
using RawReadings = std::array< uint16_t, analogPins >;
// Unconnected pins
static const std::vector< int > unconnectedDemultiplexerPinsList = {
    56, 57, 59, 61
};

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

// Each field is located between two pins
static const std::array< std::pair< int, int >, fieldsCount > fieldDefinitions = {
    {
    { 4, 6 },   // 00
    { 6, 2 },   // 01
    { 7, 2 },   // 02
    { 7, 3 },   // 03
    { 5, 3 },   // 04
    { 5, 36 },  // 05
    { 38, 36 }, // 06
    { 38, 35 }, // 07
    { 39, 35 }, // 08
    { 39, 37 }, // 09

    { 4, 1 },   // 10
    { 2, 1 },   // 11
    { 2, 0 },   // 12
    { 3, 0 },   // 13
    { 3, 34 },  // 14
    { 36, 34 }, // 15
    { 36, 33 }, // 16
    { 33, 35 }, // 17
    { 32, 35 }, // 18
    { 32, 37 }, // 19

    { 1, 14 },  // 20
    { 1, 15 },  // 21
    { 0, 15 },  // 22
    { 0, 13 },  // 23
    { 34, 13 }, // 24
    { 34, 46 }, // 25
    { 33, 46 }, // 26
    { 33, 47 }, // 27
    { 32, 47 }, // 28
    { 32, 45 }, // 29

    { 14, 12 }, // 30
    { 15, 12 }, // 31
    { 15, 11 }, // 32
    { 13, 11 }, // 33
    { 13, 44 }, // 34
    { 46, 44 }, // 35
    { 46, 41 }, // 36
    { 47, 41 }, // 37
    { 47, 40 }, // 38
    { 45, 40 }, // 39

    { 12, 10 }, // 40
    { 12, 9 },  // 41
    { 11, 9 },  // 42
    { 11, 8 },  // 43
    { 44, 8 },  // 44
    { 44, 42 }, // 45
    { 41, 42 }, // 46
    { 41, 55 }, // 47
    { 40, 55 }, // 48
    { 40, 43 }, // 49

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
    { 51, 57 }, // 78
    { 0, 0 },   // 79

    { 28, 17 }, // 80
    { 30, 17 }, // 81
    { 30, 16 }, // 82
    { 31, 16 }, // 83
    { 31, 50 }, // 84
    { 29, 50 }, // 85
    { 29, 49 }, // 86
    { 49, 58 }, // 87
    { 57, 58 }, // 88
    { 57, 59 }, // 89

    { 28, 26 }, // 90
    { 30, 26 }, // 91
    { 30, 25 }, // 92
    { 31, 25 }, // 93
    { 31, 27 }, // 94
    { 29, 27 }, // 95
    { 29, 24 }, // 96
    { 58, 24 }, // 97
    { 58, 56 }, // 98
    { 59, 56 }, // 99
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
    const auto commonInPinsCount = commonInPins.size();

    int counter = 0;

    for ( int i = 0; i < commonInPinsCount; i++ )
    {
        for ( uint8_t j = 0; j < analogPinsPerChip; j++ )
        {
            const int currentPin = i * analogPinsPerChip + j;

            // Continue if we are going to read from disabled pin
            if ( std::find( unconnectedDemultiplexerPinsList.begin(),
                            unconnectedDemultiplexerPinsList.end(),
                            currentPin ) != unconnectedDemultiplexerPinsList.end() )
            {
                continue;
            }

            // Setup demultiplexer data select pins
            for ( const auto& pair : dataSelectPairs )
            {
                digitalWrite( pair.first, j & pair.second );
            }

            readings[ counter ] = std::min( analogRead( commonInPins[ i ] ), readings[ counter ] );
            counter++;
        }
    }
}

void rawDebouncedRead( RawReadings& readings )
{
    constexpr static int maxCount = 5;

    std::array< int, std::tuple_size< RawReadings >{} > debounceCounter = {};

    int stableReadingCount = 0;
    unsigned long debounceEndTime = 0;

    // There are two levels of debouncing. One is short, for cases when user tries to press
    // on the field using two pads of his figure. The other is long and is meant for cases when user
    // has successfully pressed on the field, and needs some time to remove his figure from the field
    // to not to press on it again.
    constexpr int debounceShort = 400;
    constexpr int debounceLong = 2000;

    static Waiter waiter( debounceLong );

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
                    debounceEndTime = millis() + debounceShort;
                }
            }

            if ( debounceCounter[ i ] == maxCount )
            {
                stableReadingCount++;
            }
        }

        // If we got 2 stable reads, debouncing succeeded
        if ( stableReadingCount == 2 )
        {
            if ( waiter.isReady( millis() ) )
            {
                return;
            }
        }

        // If debounce time passed and we are still here it means that debouncing failed
        if ( millis() >= debounceEndTime )
        {
            debounceEndTime = 0;
            stableReadingCount = 0;
            debounceCounter = {};
            readings.fill( maxValue );

            // This will make sure that after the user takes off his figure, the whole
            // field will be read as "empty" and will allow to perform correct search
            // for difference between this and subsequent readings.
            return;
        }
    }
}

void read( FieldsRaw& fields )
{
    RawReadings readings;
    readings.fill( maxValue );

    rawDebouncedRead( readings );

    convert( readings, fields );
}

void readUndebounced( FieldsRaw& fields )
{
    RawReadings readings;
    readings.fill( maxValue );

    rawRead( readings );

    convert( readings, fields );
}

void convert( RawReadings& readings, FieldsRaw& fields )
{
    static_assert( std::tuple_size< decltype( fieldDefinitions ) >{} == std::tuple_size< FieldsRaw >{}, "" );

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
