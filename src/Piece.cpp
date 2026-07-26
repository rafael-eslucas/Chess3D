#include "Piece.h"

Position Piece::getPosicao() {
    return pos;
}

void Piece::setPosicao(const Position& p) {
    pos = p;
}

Color Piece::getColor() {
    return color;
}

Type Piece::getType() {
    return type;
}

std::string Piece::getId() {
    return id;
}