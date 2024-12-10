#pragma once

wire_iter_t *wire_iter_new(const wire_t *root_wire);
void wire_iter_destroy(wire_iter_t **self_pointer);
