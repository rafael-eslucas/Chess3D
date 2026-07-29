//
// Created by rafael on 29/07/2026.
//

#pragma once

#include "Piece.h"
#include "Position.h"

struct Last {
    Piece* moved;
    Position from;
    Position to;
    Piece* captured;
};