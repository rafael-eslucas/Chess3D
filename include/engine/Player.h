#include <crow.h>

#pragma once

class Game;

struct Player {
    Game& game;
    Side side;

    Player(Game& game, Side side) : game(game), side(side) {}
};

struct OnlinePlayer : Player {
    crow::websocket::connection& conn;

    OnlinePlayer(Game& game, crow::websocket::connection& conn, Side side) : Player(game, side), conn(conn) {};
};

struct OfflinePlayer : Player {
    //vou descobrir ainda
};