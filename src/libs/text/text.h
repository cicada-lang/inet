#pragma once

size_t text_max_lineno(const char *text);
size_t text_lineno_of_index(const char *text, size_t index);
void text_print_context(file_t* file, const char *text, size_t start, size_t end);
