#pragma once
#include "../include/engine/Side.h"
#include "engine/Type.h"

namespace utils {
    inline int idx(Type t) {
        return static_cast<int>(t);
    }
    inline int idx(Side side) {
        return static_cast<int>(side);
    }
}
