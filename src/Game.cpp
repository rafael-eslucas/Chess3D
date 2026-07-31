//
// Created by rafael on 30/07/2026.
//

#include "../include/Game.h"

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
}