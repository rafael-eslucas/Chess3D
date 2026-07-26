//
// Created by rafael on 22/07/2026.
//

#include "Position.h"
#include "Vector.h"

bool Position::operator==(const Position &other) const {
    return (x == other.x && y == other.y && z == other.z);
}

bool Position::operator!=(const Position &other) const {
    return !(*this == other);
}

Vector Position::operator-(const Position &other) const {
    return Vector(x - other.x, y - other.y, z - other.z);
}

Position Position::operator+(const Vector &other) const {
    return Position(x + other.x, y + other.y, z + other.z);
}

Position& Position::operator+=(const Vector &other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;

    return *this;
}