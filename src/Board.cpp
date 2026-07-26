#include "Board.h"
#include "Color.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include <iostream>
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Rules.h"

Board::Board() {
    addPiece(new Rook(1, 1, 0, Color::White, 1));
    addPiece(new Rook(0, 1, 1, Color::Black, 1));
    addPiece(new Queen(1, 2, 0, Color::White, 1));
    addPiece(new Queen(0, 2, 1, Color::Black, 1));
    addPiece(new Bishop(1, 3, 0, Color::White, 1));
    addPiece(new Bishop(0, 3, 1, Color::Black, 1));
    addPiece(new Knight(1,4,0,Color::White, 1));
    addPiece(new Knight(0,4,1,Color::Black, 1));
    addPiece(new King(1,5,0,Color::White, 1));
    addPiece(new King(0,5,1,Color::Black, 1));
    addPiece(new Pawn(1,6,0,Color::White, 1));
    addPiece(new Pawn(0,6,1,Color::Black, 1));
}

Board::~Board() {
    for (auto peca : pieces) {
        delete peca;
    }
}

void Board::move(Move move, Color color) {
    Position from = move.getFrom();
    Position to = move.getTo();

    Piece* piece = space[from.x][from.y][from.z];

    bool valid = canMove(piece, to, color);
    bool capture = Rules::canCapture(*this, to, color);

    if (valid) {
        if (capture) {
            Rules::capture(*this, to);
        }
        space[from.x][from.y][from.z] = nullptr;
        space[to.x][to.y][to.z] = piece;
        piece->setPosicao(to);
    }
}

bool Board::canMove(Piece *piece, Position to, Color color) {
    if (piece == nullptr) {
        std::cout << "Não há peça nessa posição!";
        return false;
    }

    if (piece->getColor() != color || !piece->isValid(to)  || !(this->isinside(to))) {
        return false;
    };
    bool freepath = this->isempty(piece->route(to));
    std::cout << freepath;

    return freepath && (Rules::canCapture(*this, to, color) || space[to.x][to.y][to.z] == nullptr);
}

bool Board::isempty(const std::vector<Position>& positions) {
    for (const auto& pos : positions) {
        if (space[pos.x][pos.y][pos.z] != nullptr) {
            return false;
        }
    }
    return true;
}


bool Board::isinside(const Position &pos) {
    return (pos.x >= 0 && pos.x < 8 &&
            pos.y >= 0 && pos.y < 8 &&
            pos.z >= 0 && pos.z < 8 );
}

void Board::print(int type) {
    if (type == 0) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 8; k++) {
                    if (space[k][i][j] == nullptr) {
                        std::cout << "[  ] ";
                    } else {
                        std::cout << "[" << space[k][i][j]->getId()[0] << space[k][i][j]->getId()[1] << "] ";
                    }
                } std::cout << "    ";
            } std::cout << "\n";
        } std::cout << "\n";
        for (int i = 0; i < 8; i++) {
            for (int j = 4; j < 8; j++) {
                for (int k = 0; k < 8; k++) {
                    if (space[k][i][j] == nullptr) {
                        std::cout << "[  ] ";
                    } else {
                        std::cout << "[" << space[k][i][j]->getId()[0] << space[k][i][j]->getId()[1] << "] ";
                    }
                } std::cout << "    ";
            } std::cout << "\n";
        }
    }
    else if (type == 1) {
        for (auto peca : pieces) {
            std::cout << peca->getId() << ":" << "(" << peca->getPosicao().x << peca->getPosicao().y << peca->getPosicao().z << ") \n";
        }
    }
}

Piece* Board::findKing(Color color) const {
    for (auto p : pieces) {
        if (p->getType() == Type::King && p->getColor() == color) {
            return p;
        }
    }
    return nullptr;
}

void Board::addPiece(Piece *piece) {
    if (piece != nullptr) {
        pieces.push_back(piece);
        Position p = piece->getPosicao();
        space[p.x][p.y][p.z] = piece;
    }
}

std::vector<Piece *> Board::getPieces() const {
    return pieces;
}

Piece* Board::whatIsInSpaceAt(int i, int j, int k) const {
    if (i > 0 && i < 8 && j > 0 && j < 8 && k > 0 && k < 8) {
        return space[i][j][k];
    }
    return nullptr;
}

void Board::setSpace(int i, int j, int k, Piece *piece) {
    space[i][j][k] = piece;
}
