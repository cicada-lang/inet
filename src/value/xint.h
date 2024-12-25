#pragma once

value_t xint(int64_t target);
bool is_xint(value_t value);
int64_t to_int64(value_t value);

value_t xint_add(value_t x, value_t y);
value_t xint_sub(value_t x, value_t y);
value_t xint_mul(value_t x, value_t y);
value_t xint_div(value_t x, value_t y);
value_t xint_mod(value_t x, value_t y);
