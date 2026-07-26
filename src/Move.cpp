//
// Created by rafael on 22/07/2026.
//

#include "Move.h"

Move Move::decode(const std::string& input) {
    int x, y, z;

    Position from(input[0] - '0',
                  input[1] - '0',
                  input[2] - '0');
    Position to(input[4] - '0',
                input[5] - '0',
                input[6] - '0');

    return Move(from, to);
}


Position Move::getFrom() {
    return from;
}

Position Move::getTo() {
    return to;
}