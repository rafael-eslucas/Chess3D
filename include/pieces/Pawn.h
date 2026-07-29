#pragma once

#include "Piece.h"

class Pawn : public Piece {
    public:
        Pawn(int x, int y, int z, Side color, int n) : Piece(x, y, z, color, Type::Pawn) {
            id = (color == Side::White? "W":"B");
            id += "P" + std::to_string(n);
        };
        bool isValid(const Position& to) override;
        bool isValidCapture(const Position& to) override;
        std::vector<Position> route(Position to) override;
};