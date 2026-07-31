#include <iostream>
#include "Piece.h"

Position Piece::getPosicao() {
    return pos;
}

void Piece::setPosicao(const Position& p) {
    pos = p;
}

Side Piece::getSide() {
    return color;
}

Type Piece::getType() {
    return type;
}

std::string Piece::getId() {
    return id;
}

bool Piece::isValidCapture(const Position& to) {
    return isValid(to);
}

bool Piece::isAlive() {
    return alive;
}

void Piece::setAlive(bool alive) {
    this->alive = alive;
}
