#pragma once

#include <vector>

#include "Color.h"
#include "Piece.h"
#include "Position.h"
#include "Type.h"

class Knight : public Piece {
    public:
        Knight(int x, int y, int z, Color color, int n) : Piece(x, y, z, color, Type::Knight) {
            id = (color == Color::White? "W":"B");
            id += "N" + std::to_string(n);
        };
        bool isValid(const Position& to) override;
        std::vector<Position> route(Position to) override;
};