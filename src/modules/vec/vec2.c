#include "index.h"

vec2_t
vec2_add(vec2_t first, vec2_t second) {
    return (vec2_t) {
        .x = first.x + second.x,
        .y = first.y + second.y,
    };
}

vec2_t
vec2_sub(vec2_t first, vec2_t second) {
    return (vec2_t) {
        .x = first.x - second.x,
        .y = first.y - second.y,
    };
}
