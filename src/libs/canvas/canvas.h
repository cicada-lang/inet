#pragma once

struct canvas_t {
    const char *window_name;
};

canvas_t *canvas_new(void);
void canvas_destroy(canvas_t **self_pointer);
