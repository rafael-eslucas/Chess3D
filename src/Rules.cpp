//
// Created by rafael on 24/07/2026.
//

#include "Rules.h"

#include <filesystem>
#include <iostream>

namespace Rules {
    bool isCheck(const Board& board, Side color) {
        Piece* king = board.findKing(color);
        std::vector<Piece*> pieces = board.getPieces();

        for (auto piece : pieces) {
            if (piece->getColor() == color) {
                continue;
            }
            if (board.canMove(piece, king->getPosicao(), piece->getColor())) {
                return true;
            }
        }
        return false;
    }

    bool isKingAlive(const Board &board, Side color) {
        for (auto p : board.getPieces()) {
            if (p->getType() == Type::King && p->getColor() == color) {
                return true;
            }
        } return false;
    }

    bool isThisTheEnd(const Board& board) {
        if (!Rules::isKingAlive(board, Side::White)) {
            std::cout << "Black won!";
            return true;
        } else if (!Rules::isKingAlive(board, Side::Black)) {
            std::cout << "White won!";
            return true;
        } return false;
    }

    void capture(Board& board, Position to) {
        std::cout << "\nCAPTURING\n";
        Piece* piece = board.whatIsInSpaceAt(to.x, to.y, to.z);
        board.setLastCapture(piece);
        board.kill(piece);
    }

    bool canCapture(const Board& board, Position to, Side color) {
        Piece* atackedpiece = board.whatIsInSpaceAt(to.x, to.y, to.z);

        bool freeto = atackedpiece == nullptr;
        bool capture = !freeto && (atackedpiece->getColor() != color);

        return capture;
    }

}
