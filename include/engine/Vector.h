#pragma once

class Vector {
    public:
        int x, y, z;
        Vector(int x, int y, int z) : x(x), y(y), z(z) {};
        bool operator==(const Vector &v) const;
        bool isNull() const;
        bool isPlaneDiagonal() const;
        bool isSpaceDiagonal() const;
        bool isAxis() const;
};