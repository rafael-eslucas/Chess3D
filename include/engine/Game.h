#pragma once
#include "Board.h"
#include "Side.h"
#include "Player.h"

class Game {
    std::string id;
    Side turn;
    Board* board;

    Player* white;
    Player* black;
    public:
        Game();

        bool play(Move move, Side color);

        Board* getBoard();
        void changeTurn();
        Side getTurn();

        std::string getId();
        void setId(int n);

        Player* getWhitePlayer();
        Player* getBlackPlayer();

        void setWhitePlayer(Player* player);
        void setBlackPlayer(Player* player);
};
