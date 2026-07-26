#include "Pawn.h"
#include <cmath>

bool Pawn::isValid(const Position& to) {
    Vector d = to - pos;
    if (d.isNull()) return false;

    if (color == Color::White) return (d.x == 0 && d.y == 0 && d.z == 1);
    if (color == Color::Black) return (d.x == 0 && d.y == 0 && d.z == -1);
}

std::vector<Position> Pawn::route(Position to) {
    std::vector<Position> route;

    return route;
}

bool Pawn::isValidCapture(const Position &to) {
    Vector d = to - pos;
    if (d.isNull()) return false;

    int x = abs(d.x), y = abs(d.y), z = d.z;

    if ((color == Color::Black && z != -1) ||
        (color == Color::White && z != +1)) {
        return false;
    }


    return (x == 0 && y == 1 ||
            x == 1 && y == 0 ||
            x == 1 && y == 1 );
}