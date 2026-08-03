#include "pieces/Knight.h"
#include <cmath>

bool Knight::isValid(const Position& to) {
    Vector d = this->pos - to;
    if (d.isNull()) return false;
    int x = std::abs(d.x);
    int y = std::abs(d.y);
    int z = std::abs(d.z);

    return (x == 2 && y == 1 && z == 0 ||
            x == 2 && z == 1 && y == 0 ||
            y == 2 && z == 1 && x == 0 ||
            y == 2 && x == 1 && z == 0 ||
            z == 2 && x == 1 && y == 0 ||
            z == 2 && y == 1 && x == 0 ||

            x == 2 && y == 1 && z == 1 ||
            x == 2 && z == 1 && y == 1 ||
            y == 2 && z == 1 && x == 1 ||
            y == 2 && x == 1 && z == 1 ||
            z == 2 && x == 1 && y == 1 ||
            z == 2 && y == 1 && x == 1 );
}

std::vector<Position> Knight::route(Position to) {
    std::vector<Position> route;
    return route;
}