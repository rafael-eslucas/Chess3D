#pragma once

#include "Vector.h"

class Position {
    public:
        int x, y, z;
        Position(int x, int y, int z) : x(x), y(y), z(z) {};
        bool operator==(const Position &other) const;
        bool operator!=(const Position &other) const;
        Position operator+(const Vector &other) const;
        Vector operator-(const Position &other) const;
        Position& operator+=(const Vector &other);
};