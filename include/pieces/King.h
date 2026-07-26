#pragma once

#include "Piece.h"

class King : public Piece {
    public:
        King(int x, int y, int z, Color color, int n) : Piece(x, y, z, color, Type::King) {
            id = (color == Color::White? "W":"B");
            id += "K" + std::to_string(n);
        };
        bool isValid(const Position& to) override;
        std::vector<Position> route(Position to) override;
};