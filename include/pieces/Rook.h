#pragma once

#include "../engine/Piece.h"

class Rook : public Piece{
    public:
        Rook(int x, int y, int z, Side color, int n) : Piece(x, y, z, color, Type::Rook) {
            id = (color == Side::White? "W":"B");
            id += "R" + std::to_string(n);
        };
        bool isValid(const Position& to) override;
        std::vector<Position> route(Position to) override;
};