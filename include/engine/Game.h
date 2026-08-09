#pragma once
#include "Board.h"
#include "Side.h"

class Game {
    Side turn;
    Board* board;
    public:
        Game();

    bool play(Move move, Side color);

    Board* getBoard();
        void changeTurn();
        Side getTurn();
};
