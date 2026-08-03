#include "pieces/King.h"
#include "engine/Vector.h"
#include <cmath>

bool King::isValid(const Position& to) {
    Vector d = this->pos - to;
    if (d.isNull()) return false;

    return (abs(d.x) <= 1 &&
            abs(d.y) <= 1 &&
            abs(d.z) <= 1 );
}

std::vector<Position> King::route(Position to) {
    std::vector<Position> route;

    return route;
}