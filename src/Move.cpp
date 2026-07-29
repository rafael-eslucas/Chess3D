//
// Created by rafael on 22/07/2026.
//

#include "Move.h"

#include <stdexcept>

Move Move::decode(const std::string& input) {
    if (input.size() != 7)
        throw std::invalid_argument("Formato inválido.");

    std::string id = input.substr(0, 3);

    Position to(input[4] - '0' - 1,
                input[5] - '0' - 1,
                input[6] - '0' - 1);

    return Move(id, to);
}


std::string Move::getId() {
    return id;
}

Position Move::getTo() {
    return to;
}