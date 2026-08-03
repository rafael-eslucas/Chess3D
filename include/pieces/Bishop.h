#pragma once

#include "../engine/Side.h"
#include "../engine/Piece.h"
#include <vector>

class Bishop : public Piece {
    public:
        Bishop(int x, int y, int z, Side color, int n) : Piece(x, y, z, color, Type::Bishop) {
            id = (color == Side::White? "W":"B");
            id += "B" + std::to_string(n);
        };
        bool isValid(const Position& to) override;
        std::vector<Position> route(Position to) override;
};