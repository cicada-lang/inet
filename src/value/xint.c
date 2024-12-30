#include "index.h"

// int64_t but truncate the lower 3 bits

value_t
xint(int64_t target) {
    return (value_t) ((target << 3) | XINT);
}

bool
is_xint(value_t value) {
    return value_tag(value) == XINT;
}

int64_t
to_int64(value_t value) {
    assert(is_xint(value));
    return ((int64_t) value) >> 3;
}

value_t
xint_add(value_t x, value_t y) {
    return xint(to_int64(x) + to_int64(y));
}

value_t
xint_sub(value_t x, value_t y) {
    return xint(to_int64(x) - to_int64(y));
}

value_t
xint_mul(value_t x, value_t y) {
    return xint(to_int64(x) * to_int64(y));
}

value_t
xint_div(value_t x, value_t y) {
    return xint(to_int64(x) / to_int64(y));
}

value_t
xint_mod(value_t x, value_t y) {
    return xint(to_int64(x) % to_int64(y));
}

value_t
xint_to_xfloat(value_t x) {
    if (!is_xint(x)) {
        fprintf(stderr, "[xint_to_xfloat] type mismatch\n");
        exit(1);
    }

    return xfloat((double) to_int64(x));
}
