#pragma once

struct Coord {
    constexpr static int empty = -1;

    int x = empty;
    int y = empty;

    bool isEmpty() const {
        return x == empty && y == empty;
    }
};