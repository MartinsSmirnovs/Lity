#pragma once

#include <RGB.h>
#include <map>
#include <vector>

class Field {
public:
    enum Type {
        black  = -4,
        build3 = -3,
        build2 = -2,
        build1 = -1,
        white  = 0,
        blue   = 738,
        red    = 1540,
        green  = 2457,
        purple = 3276,
        eraser = 4076
    };

    Field() noexcept = default;
    Field(int value);

    RGB getColor() const;
    Type getType() const;

private:
    using TypeList = std::vector<Type>;

    static const std::map<Type, RGB> typeColorMap;
    static const TypeList typeList;
    constexpr static int digitalRange = 200;

    Type type;

    bool inRange(Type target, int value) const;

    TypeList::const_iterator closest(const TypeList& list, int value) const;
};