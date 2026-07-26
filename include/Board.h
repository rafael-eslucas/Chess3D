#pragma once

#include <vector>

#include "Move.h"
#include "Piece.h"
#include "Position.h"
#include "Color.h"

class Board {
    std::vector<Piece*> pieces;
    Piece* space[8][8][8] = {};
    public:
        Board();
        ~Board();
        void move(Move move, Color color);
        bool isempty(const std::vector<Position>& positions);
        bool isinside(const Position& pos);
        void print(int type);
        void addPiece(Piece* piece);
        bool canMove(Piece* piece, Position to, Color color);
        Piece* findKing(Color color) const;
        std::vector<Piece*> getPieces() const;
        Piece* whatIsInSpaceAt(int i, int j, int k) const;
        void setSpace(int i, int j, int k, Piece* piece);
};