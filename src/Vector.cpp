//
// Created by rafael on 23/07/2026.
//

#include <cmath>
#include "Vector.h"

bool Vector::operator==(const Vector &v) const {
    return (x == v.x && y == v.y && z == v.z);
}

bool Vector::isNull() const {
    return (x == 0 && y == 0 && z == 0);
}

bool Vector::isAxis() const {
    return (x == 0 && y == 0 && z != 0) ||
           (x == 0 && y != 0 && z == 0) ||
           (x != 0 && y == 0 && z == 0);
}

bool Vector::isPlaneDiagonal() const {
    return ((std::abs(x) == std::abs(x) && x == 0) ||
            (std::abs(y) == std::abs(y) && y == 0) ||
            (std::abs(z) == std::abs(z) && z == 0) );
}

bool Vector::isSpaceDiagonal() const {
    return (x != 0 &&
            std::abs(x) == std::abs(y) &&
            std::abs(x) == std::abs(z) );
}