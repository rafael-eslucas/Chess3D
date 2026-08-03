#include "pieces/Rook.h"
#include "engine/Vector.h"
#include <cmath>

bool Rook::isValid(const Position& to) {
    Vector d = this->pos - to;
    if (d.isNull()) return false;

    return d.isAxis();
}

std::vector<Position> Rook::route(Position to) {
    std::vector<Position> route;
    if (!isValid(to)) {
        return route;
    }

    Position temp = pos;

    Vector d = to - pos;

    d.x = d.x == 0 ? 0 : d.x/std::abs(d.x);
    d.y = d.y == 0 ? 0 : d.y/std::abs(d.y);
    d.z = d.z == 0 ? 0 : d.z/std::abs(d.z);

    while (temp + d != to) {
        temp += d;
        route.push_back(temp);
    }

    return route;
}