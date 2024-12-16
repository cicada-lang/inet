#pragma once

struct vec2_t { double x, y; };

vec2_t vec2_add(vec2_t v1, vec2_t v2);
vec2_t vec2_sub(vec2_t v1, vec2_t v2);
vec2_t vec2_neg(vec2_t v);
vec2_t vec2_mul(vec2_t v1, vec2_t v2);
double vec2_dot(vec2_t v1, vec2_t v2);
