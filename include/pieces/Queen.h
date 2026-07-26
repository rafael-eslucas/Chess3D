#pragma once

#include "Piece.h"

class Queen : public Piece {
    public:
        Queen(int x, int y, int z, Color color, int n) : Piece(x, y, z, color, Type::Queen) {
            id = (color == Color::White? "W":"B");
            id += "Q" + std::to_string(n);
        };
        bool isValid(const Position& to) override;
        std::vector<Position> route(Position to) override;
};