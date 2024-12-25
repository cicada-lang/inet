#include "index.h"

// double-precision floating-point but truncate the lower 3 bits

typedef union { double as_double; uint64_t as_uint64; } double_or_uint64_t;

value_t
xfloat(double target) {
    double_or_uint64_t the_union = (double_or_uint64_t) {
        .as_double = target
    };

    return (value_t) ((the_union.as_uint64 & DATA_MASK) | XFLOAT);
}

bool
is_xfloat(value_t value) {
    return value_tag(value) == XFLOAT;
}

double
to_double(value_t value) {
    assert(is_xfloat(value));

    double_or_uint64_t the_union = (double_or_uint64_t) {
        .as_uint64 = ((uint64_t) value) & DATA_MASK
    };

    return the_union.as_double;
}

value_t
xfloat_add(value_t x, value_t y) {
    return xfloat(to_double(x) + to_double(y));
}

value_t
xfloat_sub(value_t x, value_t y) {
    return xfloat(to_double(x) - to_double(y));
}

value_t
xfloat_mul(value_t x, value_t y) {
    return xfloat(to_double(x) * to_double(y));
}

value_t
xfloat_div(value_t x, value_t y) {
    return xfloat(to_double(x) / to_double(y));
}

value_t
xfloat_mod(value_t x, value_t y) {
    return xfloat(fmod(to_double(x), to_double(y)));
}
