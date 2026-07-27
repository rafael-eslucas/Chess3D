#pragma once

#include <string>

#include "Piece.h"
#include "Position.h"

class Move {
    std::string id;
    Position to;
    public:
        Move(std::string id, Position to) : id(id), to(to) {};
        Move(std::string id, int x, int y, int z) : id(id), to(x, y, z) {};
        Move() : id(""), to(0,0,0) {};
        static Move decode(const std::string &input);
        static Move code(const std::string &input);
        std::string getId();
        Position getTo();
};