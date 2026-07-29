#include "raylib.h"

#include "Board.h"
#include "Side.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include <iostream>
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Rules.h"

Board::Board() {
    addPiece(new Rook(1, 1, 0, Side::White, 1));
    addPiece(new Rook(0, 1, 1, Side::Black, 1));
    addPiece(new Queen(1, 2, 0, Side::White, 1));
    addPiece(new Queen(0, 2, 1, Side::Black, 1));
    addPiece(new Bishop(1, 3, 0, Side::White, 1));
    addPiece(new Bishop(0, 3, 1, Side::Black, 1));
    addPiece(new Knight(1,4,0,Side::White, 1));
    addPiece(new Knight(0,4,1,Side::Black, 1));
    addPiece(new King(1,5,0,Side::White, 1));
    addPiece(new King(0,5,1,Side::Black, 1));
    addPiece(new Pawn(1,6,0,Side::White, 1));
    addPiece(new Pawn(0,6,1,Side::Black, 1));
}

Board::~Board() {
    for (auto peca : pieces) {
        delete peca;
    }
}

void Board::move(Move move, Side color) {
    std::string id = move.getId();
    Piece* piece = whichPieceIsThis(id);
    if (!piece)
        return;
    Position to = move.getTo();
    Position from = piece->getPosicao();

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

bool Board::canMove(Piece *piece, Position to, Side color) const {
    if (piece == nullptr) {
        std::cout << "Não há peça nessa posição!";
        return false;
    }

    bool cancapture = Rules::canCapture(*this, to, color);
    bool freepath = this->isempty(piece->route(to));

    if (piece->getColor() != color || !(this->isinside(to))) {
        return false;
    }

    bool valid = piece->isValid(to);

    if (piece->getType() == Type::Pawn && cancapture) {
        valid = piece->isValidCapture(to);
    }

    return valid && freepath && (cancapture || space[to.x][to.y][to.z] == nullptr);
}

bool Board::isempty(const std::vector<Position>& positions) const{
    for (const auto& pos : positions) {
        if (space[pos.x][pos.y][pos.z] != nullptr) {
            return false;
        }
    }
    return true;
}


bool Board::isinside(const Position &pos) const {
    return (pos.x >= 0 && pos.x < 8 &&
            pos.y >= 0 && pos.y < 8 &&
            pos.z >= 0 && pos.z < 8 );
}

void Board::print(int type) {
    if (type == 0) {
        for (int j = 0; j < 4; j++) {
            std::cout << "  ";
            for (int k = 0; k < 8; k++) {
                std::cout << " " << k+1 << "   ";
            } std::cout << "    ";
        } std::cout << std::endl;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << i+1 << " ";
                for (int k = 0; k < 8; k++) {
                    if (space[k][i][j] == nullptr) {
                        std::cout << "[  ] ";
                    } else {
                        std::cout << "[" << space[k][i][j]->getId()[0] << space[k][i][j]->getId()[1] << "] ";
                    }
                } std::cout << "    ";
            } std::cout << "\n";
        } std::cout << "\n";

        for (int j = 0; j < 4; j++) {
            std::cout << "  ";
            for (int k = 0; k < 8; k++) {
                std::cout << " " << k+1 << "   ";
            } std::cout << "    ";
        } std::cout << std::endl;
        for (int i = 0; i < 8; i++) {
            for (int j = 4; j < 8; j++) {
                std::cout << i+1 << " ";
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

Piece* Board::findKing(Side color) const {
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

std::vector<Piece*> Board::getPieces() const{
    return pieces;
}

void Board::deletePiece(Piece *piece) {
    for (int i = 0; i < pieces.size(); i++) {
        if (pieces[i] == piece) {
            pieces.erase(pieces.begin() + i);
            space[piece->getPosicao().x][piece->getPosicao().y][piece->getPosicao().z] = nullptr;
            delete piece;
            break;
        }
    }
}

Piece* Board::whatIsInSpaceAt(int i, int j, int k) const {
    if (i >= 0 && i <= 7 && j >= 0 && j <= 7 && k >= 0 && k <= 7) {
        return space[i][j][k];
    }
    return nullptr;
}

void Board::setSpace(int i, int j, int k, Piece *piece) {
    space[i][j][k] = piece;
}

Piece *Board::whichPieceIsThis(std::string id) const {
    for (auto p : pieces) {
        if (p->getId() == id) {
            return p;
        }
    } return nullptr;
}


void Board::ray() {
    InitWindow(1200, 780, "Chess3D");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);



        EndDrawing();
    }
}
