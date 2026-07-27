#pragma once

#include <vector>

#include "Side.h"
#include "Piece.h"
#include "Position.h"
#include "Type.h"

class Knight : public Piece {
    public:
        Knight(int x, int y, int z, Side color, int n) : Piece(x, y, z, color, Type::Knight) {
            id = (color == Side::White? "W":"B");
            id += "N" + std::to_string(n);
        };
        bool isValid(const Position& to) override;
        std::vector<Position> route(Position to) override;
};