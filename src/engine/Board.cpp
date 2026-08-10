#include "raylib.h"

#include "engine/Board.h"
#include "engine/Side.h"
#include "pieces/Rook.h"
#include "pieces/Bishop.h"
#include "pieces/Queen.h"
#include <iostream>
#include "pieces/King.h"
#include "pieces/Knight.h"
#include "pieces/Pawn.h"
#include "engine/Rules.h"

Board::Board() {
    /* ========== WHITE ========== */
    addPiece(new Rook(0, 0, 0, Side::White, 1));
    addPiece(new Rook(5,0,0,Side::White, 2));
    addPiece(new Rook(0,5,0, Side::White, 3));
    addPiece(new Rook(5,5,0, Side::White, 4));

    addPiece(new Bishop(2, 0, 0, Side::White, 1));
    addPiece(new Bishop(3, 0, 0, Side::White, 2));
    addPiece(new Bishop(0, 2, 0, Side::White, 3));
    addPiece(new Bishop(0, 3, 0, Side::White, 4));
    addPiece(new Bishop(2, 5, 0, Side::White, 5));
    addPiece(new Bishop(3, 5, 0, Side::White, 6));
    addPiece(new Bishop(5, 2, 0, Side::White, 7));
    addPiece(new Bishop(5, 3, 0, Side::White, 8));

    addPiece(new Knight(1,1,0,Side::White, 1));
    addPiece(new Knight(4,1,0,Side::White, 2));
    addPiece(new Knight(4,4,0,Side::White, 3));
    addPiece(new Knight(1,4,0,Side::White, 4));

    addPiece(new Pawn(2,3,0,Side::White, 1));
    addPiece(new Pawn(3,2,0,Side::White, 2));

    addPiece(new Queen(2, 2, 0, Side::White, 1));
    addPiece(new King(3, 3, 0, Side::White, 1));
    int n = 3;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            addPiece(new Pawn(i,j,1,Side::White, n));
            n++;
        }
    }

    /* ========== BLACK ========== */
    addPiece(new Rook(0, 0, 5, Side::Black, 1));
    addPiece(new Rook(5,0,5,Side::Black, 2));
    addPiece(new Rook(0,5,5, Side::Black, 3));
    addPiece(new Rook(5,5,5, Side::Black, 4));

    addPiece(new Bishop(2, 0, 5, Side::Black, 1));
    addPiece(new Bishop(3, 0, 5, Side::Black, 2));
    addPiece(new Bishop(0, 2, 5, Side::Black, 3));
    addPiece(new Bishop(0, 3, 5, Side::Black, 4));
    addPiece(new Bishop(2, 5, 5, Side::Black, 5));
    addPiece(new Bishop(3, 5, 5, Side::Black, 6));
    addPiece(new Bishop(5, 2, 5, Side::Black, 7));
    addPiece(new Bishop(5, 3, 5, Side::Black, 8));

    addPiece(new Knight(1,1,5,Side::Black, 1));
    addPiece(new Knight(4,1,5,Side::Black, 2));
    addPiece(new Knight(4,4,5,Side::Black, 3));
    addPiece(new Knight(1,4,5,Side::Black, 4));

    addPiece(new Pawn(2,3,5,Side::Black, 1));
    addPiece(new Pawn(3,2,5,Side::Black, 2));

    addPiece(new Queen(2, 2, 5, Side::Black, 1));
    addPiece(new King(3, 3, 5, Side::Black, 1));

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            addPiece(new Pawn(i,j,4,Side::Black, i * 6 + j + 3));
        }
    }
}

Board::~Board() {
    for (auto peca : pieces) {
        delete peca;
    }
}

bool Board::move(Move move, Side color) {
    std::string id = move.getId();
    Piece* piece = whichPieceIsThis(id);
    if (!piece) {
        return false;
    }
    std::cout << "Piece " << piece->getId() << " is being moved" << std::endl;
    if (!piece) {
        return false;
    }
    Position to = move.getTo();
    Position from = piece->getPosicao();
    std::cout << "FROM: " << from.x << " " <<from.y << " " << from.z << " TO: " << to.x << " " << to.y << " " << to.z << std::endl;

    bool valid = canMove(piece, to, color);
    std::cout << "VALID: " << valid << std::endl;
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
    return valid;
}

bool Board::play(Move move, Side color) {
    std::cout << "PLAYING" << std::endl;
    if (!this->move(move, color))
        return false;

    if (Rules::isCheck(*this, color)) {
        undo();
        std::cout << "Movimento inválido: Cheque";
        return false;
    }
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


    if (piece->getSide() != color) {
        std::cout << "COLOR: PIECE: " << (piece->getSide()==Side::White? "white" : "black") << " TURN: " << (color==Side::White? "white" : "black") << std::endl;
        return false;
    }
    if (!this->isinside(to)) {
        std::cout << "NOTINSIDE" << std::endl;
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
        for (int l = 2; l <= 6; l+=2) {
            for (int j = 0; j < 2; j++) {
                std::cout << "  ";
                for (int k = 0; k < 6; k++) {
                    std::cout << "   " << k+1 << "   ";
                } std::cout << "    ";
            } std::cout << std::endl;
            for (int i = 0; i < 6; i++) {
                for (int j = l-2; j < l; j++) {
                    std::cout << i+1 << " ";
                    for (int k = 0; k < 6; k++) {
                        if (space[k][i][j] == nullptr) {
                            std::cout << "[    ] ";
                        } else {
                            std::cout << "[" << space[k][i][j]->getId().substr(0, 4) << "] ";
                        }
                    } std::cout << "    ";
                } std::cout << "\n";
            } std::cout << "\n";
        }

        /*
        for (int j = 0; j < 3; j++) {
            std::cout << "  ";
            for (int k = 0; k < 6; k++) {
                std::cout << "  " << k+1 << "   ";
            } std::cout << "    ";
        } std::cout << std::endl;
        for (int i = 0; i < 6; i++) {
            for (int j = 3; j < 6; j++) {
                std::cout << i+1 << " ";
                for (int k = 0; k < 6; k++) {
                    if (space[k][i][j] == nullptr) {
                        std::cout << "[   ] ";
                    } else {
                        std::cout << "[" << space[k][i][j]->getId().substr(0, 3) << "] ";
                    }
                } std::cout << "    ";
            } std::cout << "\n";
        }*/
    }
    else if (type == 1) {
        Type t = Type::Rook;
        for (auto peca : pieces) {
            std::cout << peca->getId() << ":" << "(" << peca->getPosicao().x << peca->getPosicao().y << peca->getPosicao().z << ")  ";
            if (t != peca->getType()) {
                std::cout << "\n";
            } t = peca->getType();
        }
    }
}

Piece* Board::findKing(Side color) const {
    for (auto p : pieces) {
        if (p->getType() == Type::King && p->getSide() == color) {
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