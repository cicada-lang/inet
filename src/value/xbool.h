#pragma once

#define xtrue ((value_t) 0x00ffffffffffffff)
#define xfalse ((value_t) 0x01ffffffffffffff)

value_t xbool(bool target);
bool is_xbool(value_t value);
bool to_bool(value_t value);

value_t xbool_and(value_t x, value_t y);
value_t xbool_or(value_t x, value_t y);
value_t xbool_not(value_t x);
