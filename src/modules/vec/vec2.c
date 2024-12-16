#include "index.h"

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
