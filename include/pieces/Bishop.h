#pragma once

#include "Color.h"
#include "Piece.h"
#include <vector>

class Bishop : public Piece {
    public:
        Bishop(int x, int y, int z, Color color, int n) : Piece(x, y, z, color, Type::Bishop) {
            id = (color == Color::White? "W":"B");
            id += "B" + std::to_string(n);
        };
        bool isValid(const Position& to) override;
        std::vector<Position> route(Position to) override;
};