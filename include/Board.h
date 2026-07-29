#pragma once

#include <vector>

#include "Move.h"
#include "Piece.h"
#include "Position.h"
#include "Side.h"
#include "Last.h"

class Board {
    std::vector<Piece*> pieces;
    Piece* space[6][6][6] = {};
    Last last;
    public:
        Board();
        ~Board();
        bool play(Move move, Side color);
        bool move(Move move, Side color);
        bool isempty(const std::vector<Position>& positions) const;
        bool isinside(const Position& pos) const;
        void print(int type);
        void addPiece(Piece* piece);
        bool canMove(Piece* piece, Position to, Side color) const;
        Piece* findKing(Side color) const;
        std::vector<Piece*> getPieces() const;
        void kill(Piece* piece);
        Piece* whatIsInSpaceAt(int i, int j, int k) const;
        void setSpace(int i, int j, int k, Piece* piece);
        Piece* whichPieceIsThis(std::string id) const;
        void undo();
        void setLastCapture(Piece* piece);

        void ray();
};