#pragma once

#include <string>

#include "Position.h"
#include "Side.h"
#include <vector>
#include "Type.h"

class Piece {
    protected:
        Position pos;
        Type type;
        Side color;
        std::string id;
    public:
        Piece(int x, int y, int z, Side color, Type type) : pos(x, y, z), color(color), type(type) {};
        virtual bool isValid(const Position& to) = 0;
        Position getPosicao();
        void setPosicao(const Position& p);
        Side getColor();
        Type getType();
        virtual std::vector<Position> route(Position para) = 0;
        std::string getId();
};