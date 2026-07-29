#include <iostream>
#include "Pawn.h"
#include <cmath>

bool Pawn::isValid(const Position& to) {
    Vector d = to - pos;
    if (d.isNull()) return false;

    if (color == Side::White) return (d.x == 0 && d.y == 0 && d.z == 1);
    if (color == Side::Black) return (d.x == 0 && d.y == 0 && d.z == -1);
}

std::vector<Position> Pawn::route(Position to) {
    std::vector<Position> route;

    return route;
}

bool Pawn::isValidCapture(const Position &to) {
    std::cout << "Pawn";
    Vector d = to - pos;
    if (d.isNull()) return false;

    int x = abs(d.x), y = abs(d.y), z = d.z;

    if ((color == Side::Black && z != -1) ||
        (color == Side::White && z != +1)) {
        return false;
    }


    return (x == 0 && y == 1 ||
            x == 1 && y == 0 ||
            x == 1 && y == 1 );
}