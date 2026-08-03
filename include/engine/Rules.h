#pragma once

#include "Board.h"
#include "Position.h"

namespace Rules {
    bool isCheck(const Board& board, Side color);
    bool isKingAlive(const Board& board, Side color);
    bool isThisTheEnd(const Board& board);
    void capture(Board& board, Position to);
    bool canCapture(const Board& board, Position to, Side color);
}