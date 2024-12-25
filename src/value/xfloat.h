#pragma once

value_t xfloat(double target);
bool is_xfloat(value_t value);
double to_double(value_t value);

value_t xfloat_add(value_t x, value_t y);
value_t xfloat_sub(value_t x, value_t y);
value_t xfloat_mul(value_t x, value_t y);
value_t xfloat_div(value_t x, value_t y);
value_t xfloat_mod(value_t x, value_t y);
