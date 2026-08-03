#pragma once

#include "../engine/Piece.h"

class King : public Piece {
    public:
        King(int x, int y, int z, Side color, int n) : Piece(x, y, z, color, Type::King) {
            id = (color == Side::White? "W":"B");
            id += "K" + std::to_string(n);
        };
        bool isValid(const Position& to) override;
        std::vector<Position> route(Position to) override;
};