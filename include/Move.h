#pragma once

#include <string>
#include "Position.h"

class Move {
    Position from, to;
    public:
        Move(Position from, Position to) : from(from), to(to) {};
        Move(int a, int b, int c, int x, int y, int z) : from(a, b, c), to(x, y, z) {};
        Move() : from(0,0,0), to(0,0,0) {};
        static Move decode(const std::string &input);
        static Move code(const std::string &input);
        Position getFrom();
        Position getTo();
};