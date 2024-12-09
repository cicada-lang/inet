#pragma once

uint8_t utf8_char_length(char c);
code_point_t utf8_decode(const char *string);
size_t utf8_string_length(const char *string);
void utf8_encode_into(code_point_t code_point, char *dest);
char *utf8_encode(code_point_t code_point);
