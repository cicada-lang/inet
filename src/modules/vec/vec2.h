#pragma once

struct vec2_t { double x, y; };

vec2_t vec2_zeros(void);
vec2_t vec2_ones(void);

bool vec2_equal(vec2_t v1, vec2_t v2);

vec2_t vec2_add(vec2_t v1, vec2_t v2);
vec2_t vec2_sub(vec2_t v1, vec2_t v2);
vec2_t vec2_neg(vec2_t v);
vec2_t vec2_mul(vec2_t v1, vec2_t v2);

double vec2_dot(vec2_t v1, vec2_t v2);
double vec2_square(vec2_t v);
double vec2_length(vec2_t v);

bool vec2_is_nan(vec2_t v);

vec2_t vec2_add_scalar(vec2_t v, double s);
vec2_t vec2_sub_scalar(vec2_t v, double s);
vec2_t vec2_mul_scalar(vec2_t v, double s);
vec2_t vec2_div_scalar(vec2_t v, double s);

vec2_t vec2_map(vec2_t v, double_unary_fn_t* fn);
