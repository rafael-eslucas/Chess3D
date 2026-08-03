#pragma once

#include "../engine/Piece.h"

class Queen : public Piece {
    public:
        Queen(int x, int y, int z, Side color, int n) : Piece(x, y, z, color, Type::Queen) {
            id = (color == Side::White? "W":"B");
            id += "Q" + std::to_string(n);
        };
        bool isValid(const Position& to) override;
        std::vector<Position> route(Position to) override;
};