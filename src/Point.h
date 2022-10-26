#pragma once

class Point {
public:
    Point() = default;
    Point(int y, int x);

    constexpr static int empty = -1;

    int y = empty;
    int x = empty;

    bool isEmpty() const;
    bool hasNegative() const;

    Point operator+(const Point& first) const;
    Point operator-(const Point& first) const;

    bool operator==(const Point& first) const;
    bool operator!=(const Point& first) const;
};
