#pragma once

font_t *font_new(void);
void font_destroy(font_t **self_pointer);

font_t *font_load_hex_file(file_t *file);
