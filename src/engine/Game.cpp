#include <format>
#include "engine/Game.h"

Board *Game::getBoard() {
    return this->board;
}

Side Game::getTurn() {
    return turn;
}

void Game::changeTurn() {
    turn = (turn == Side::White? Side::Black : Side::White);
}

Game::Game(){
    this->board = new Board();
    this->turn = Side::White;
    this->white = nullptr;
    this->black = nullptr;
}

bool Game::play(Move move, Side color) {
    if (this->board->play(move, color)) {
        this->changeTurn();
        return true;
    }
    return false;
}

std::string Game::getId() {
    return id;
}

void Game::setId(int n) {
    this->id = std::format("{:02X}", n);
    std::cout << this->id << std::endl;
}

Player *Game::getWhitePlayer() {
    return this->white;
}

Player *Game::getBlackPlayer() {
    return this->black;
}

void Game::setBlackPlayer(Player *player) {
    black = player;
}
void Game::setWhitePlayer(Player *player) {
    white = player;
}
