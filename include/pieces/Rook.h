#pragma once

#include "Piece.h"

class Rook : public Piece{
    public:
        Rook(int x, int y, int z, Color color, int n) : Piece(x, y, z, color, Type::Rook) {
            id = (color == Color::White? "W":"B");
            id += "R" + std::to_string(n);
        };
        bool isValid(const Position& to) override;
        std::vector<Position> route(Position to) override;
};