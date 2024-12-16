#include "index.h"

vec2_t
vec2_zeros(void) {
    return (vec2_t) { .x = 0, .y = 0 };
}

vec2_t
vec2_ones(void) {
    return (vec2_t) { .x = 1, .y = 1 };
}

bool
vec2_equal(vec2_t v1, vec2_t v2) {
    return v1.x == v2.x && v1.y == v2.y;
}

vec2_t
vec2_add(vec2_t v1, vec2_t v2) {
    return (vec2_t) {
        .x = v1.x + v2.x,
        .y = v1.y + v2.y,
    };
}

vec2_t
vec2_sub(vec2_t v1, vec2_t v2) {
    return (vec2_t) {
        .x = v1.x - v2.x,
        .y = v1.y - v2.y,
    };
}

vec2_t
vec2_neg(vec2_t v) {
    return (vec2_t) {
        .x = - v.x,
        .y = - v.y,
    };
}

vec2_t
vec2_mul(vec2_t v1, vec2_t v2) {
    return (vec2_t) {
        .x = v1.x * v2.x,
        .y = v1.y * v2.y,
    };
}

double
vec2_dot(vec2_t v1, vec2_t v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

double
vec2_square(vec2_t v) {
    return vec2_dot(v, v);
}

double
vec2_length(vec2_t v) {
    return sqrt(vec2_square(v));
}

bool
vec2_is_nan(vec2_t v) {
    return isnan(v.x) || isnan(v.y);
}

vec2_t
vec2_add_scalar(vec2_t v, double s) {
    return (vec2_t) {
        .x = v.x + s,
        .y = v.y + s,
    };
}

vec2_t
vec2_sub_scalar(vec2_t v, double s) {
    return (vec2_t) {
        .x = v.x - s,
        .y = v.y - s,
    };
}

vec2_t
vec2_mul_scalar(vec2_t v, double s) {
    return (vec2_t) {
        .x = v.x * s,
        .y = v.y * s,
    };
}

vec2_t
vec2_div_scalar(vec2_t v, double s) {
    return (vec2_t) {
        .x = v.x / s,
        .y = v.y / s,
    };
}

vec2_t
vec2_map(vec2_t v, double_unary_fn_t* fn) {
    return (vec2_t) {
        .x = fn(v.x),
        .y = fn(v.y),
    };
}
