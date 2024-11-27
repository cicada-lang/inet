#include "index.h"

canvas_t *
canvas_new(void) {
    canvas_t *self = allocate(sizeof(canvas_t));
    return self;
}
