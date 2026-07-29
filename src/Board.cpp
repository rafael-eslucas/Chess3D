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
    addPiece(new Rook(0, 0, 0, Side::White, 1));
    addPiece(new Rook(5, 0, 2, Side::Black, 1));
    addPiece(new Queen(0, 1, 0, Side::White, 1));
    addPiece(new Queen(5, 1, 2, Side::Black, 1));
    addPiece(new Bishop(0, 2, 0, Side::White, 1));
    addPiece(new Bishop(5, 2, 2, Side::Black, 1));
    addPiece(new Knight(0,3,0,Side::White, 1));
    addPiece(new Knight(5,3,2,Side::Black, 1));
    addPiece(new King(0,4,0,Side::White, 1));
    addPiece(new King(5,4,2,Side::Black, 1));
    addPiece(new Pawn(0,5,0,Side::White, 1));
    addPiece(new Pawn(5,5,2,Side::Black, 1));
}

Board::~Board() {
    for (auto peca : pieces) {
        delete peca;
    }
}

bool Board::move(Move move, Side color) {
    std::string id = move.getId();
    Piece* piece = whichPieceIsThis(id);
    if (!piece)
        return false;
    Position to = move.getTo();
    Position from = piece->getPosicao();

    bool valid = canMove(piece, to, color);
    bool capture = Rules::canCapture(*this, to, color);

    if (valid) {
        this->last.moved = piece;
        this->last.captured = nullptr;
        this->last.from = piece->getPosicao();
        this->last.to = to;
        std::cout << "\n" << last.moved->getId();

        if (capture) {
            Rules::capture(*this, to);
        }
        space[from.x][from.y][from.z] = nullptr;
        space[to.x][to.y][to.z] = piece;
        piece->setPosicao(to);
    }
    std::cout << "Valid: " << valid << std::endl;
    return valid;
}

bool Board::play(Move move, Side color) {
    if (!this->move(move, color))
        return false;

    if (Rules::isCheck(*this, color)) {
        undo();
        std::cout << "Movimento inválido: Cheque";
        return false;
    }
    std::cout << "\nPASSOUVERIFICAÇAOPLAY\n";
    return true;
}


void Board::setLastCapture(Piece* piece) {
    last.captured = piece;
}

bool Board::canMove(Piece *piece, Position to, Side color) const {
    if (piece == nullptr) {
        std::cout << "Não há peça nessa posição!";
        return false;
    }

    bool cancapture = Rules::canCapture(*this, to, color);
    bool freepath = this->isempty(piece->route(to));
    bool check = false;


    if (piece->getColor() != color || !(this->isinside(to))) {
        return false;
    }

    bool valid = piece->isValid(to);

    if (piece->getType() == Type::Pawn && cancapture) {
        valid = piece->isValidCapture(to);
    }

    return valid && freepath && (cancapture || space[to.x][to.y][to.z] == nullptr) && !check;
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
    return (pos.x >= 0 && pos.x < 6 &&
            pos.y >= 0 && pos.y < 6 &&
            pos.z >= 0 && pos.z < 6 );
}

void Board::print(int type) {
    if (type == 0) {
        for (int j = 0; j < 3; j++) {
            std::cout << "  ";
            for (int k = 0; k < 6; k++) {
                std::cout << " " << k+1 << "   ";
            } std::cout << "    ";
        } std::cout << std::endl;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                std::cout << i+1 << " ";
                for (int k = 0; k < 6; k++) {
                    if (space[k][i][j] == nullptr) {
                        std::cout << "[  ] ";
                    } else {
                        std::cout << "[" << space[k][i][j]->getId()[0] << space[k][i][j]->getId()[1] << "] ";
                    }
                } std::cout << "    ";
            } std::cout << "\n";
        } std::cout << "\n";

        for (int j = 0; j < 3; j++) {
            std::cout << "  ";
            for (int k = 0; k < 6; k++) {
                std::cout << " " << k+1 << "   ";
            } std::cout << "    ";
        } std::cout << std::endl;
        for (int i = 0; i < 6; i++) {
            for (int j = 3; j < 6; j++) {
                std::cout << i+1 << " ";
                for (int k = 0; k < 6; k++) {
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

void Board::kill(Piece *piece) {
    for (int i = 0; i < pieces.size(); i++) {
        if (pieces[i] == piece) {
            space[piece->getPosicao().x][piece->getPosicao().y][piece->getPosicao().z] = nullptr;
            piece->setAlive(false);
            break;
        }
    }
}

Piece* Board::whatIsInSpaceAt(int i, int j, int k) const {
    if (i >= 0 && i <= 5 && j >= 0 && j <= 5 && k >= 0 && k <= 5) {
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

void Board::undo() {
    std::cout << "\nUNDOING\n";
    space[last.to.x][last.to.y][last.to.z] = last.captured;
    if (last.captured) {
        last.captured->setAlive(true);
    }
    space[last.from.x][last.from.y][last.from.z] = last.moved;
    last.moved->setPosicao(last.from);
}

void Board::ray() {
    InitWindow(1280, 720, "Chess3D");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);



        EndDrawing();
    }

    CloseWindow();
}
