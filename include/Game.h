#pragma once
#include "Board.h"
#include "Side.h"

class Game {
    Side turn;
    Board* board;
    public:
        Game();
        Board* getBoard();
        void changeTurn();
        Side getTurn();
};
