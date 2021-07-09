#include "math.h"

int64_t crumb_max(int64_t lhs, int64_t rhs) {
    return lhs > rhs ? lhs : rhs;
}

int64_t crumb_min(int64_t lhs, int64_t rhs) {
    return lhs > rhs ? rhs : lhs;
}
