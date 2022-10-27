#pragma once

#include "RGB.h"
#include <map>
#include <vector>

class Field {
public:
    enum Type {
        white  = 0,
        blue   = 738,
        red    = 1540,
        green  = 2457,
        purple = 3276,
        black  = 4076,
        none   = 4095
    };

    enum class Building {
        levelNone,
        levelFirst,
        levelSecond,
        levelThird
    };

    Field() noexcept = default;
    explicit Field(uint16_t value);

    void setType(Type type);

    Type getType() const;
    Building getBuilding() const;
    const RGB& getColor() const;

    // returns true if upgraded building, false if did not
    bool upgrade();

    bool operator==(const Field& first) const;

    bool isNone() const;

private:
    Type type         = black;
    Building building = Building::levelNone;

    using TypeList = std::vector<Type>;

    static const std::map<Type, RGB> typeColorMap;
    static const TypeList typeList;
    constexpr static int digitalRange = 200;

    static bool inRange(Type target, int value);
    static TypeList::const_iterator closest(const TypeList& list, int value);
};