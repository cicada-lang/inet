#pragma once

size_t code_max_lineno(const char *string);
size_t code_lineno_of_index(const char *string, size_t index);
void code_print_context(file_t* file, const char *string, size_t start, size_t end);
