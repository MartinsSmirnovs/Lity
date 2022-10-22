#pragma once

struct Coord {
    constexpr static int empty = -1;

    int y = empty;
    int x = empty;

    bool isEmpty() const {
        return x == empty && y == empty;
    }
};