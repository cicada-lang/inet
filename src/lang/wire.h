#pragma once

// `wire_t` does NOT own `node` and `opposite_wire`.

struct wire_t {
    node_t *node;
    wire_index_t index;
    wire_t *opposite_wire;
};

wire_t *wire_new(void);
void wire_destroy(wire_t **self_pointer);

bool wire_is_principal(wire_t *self);

const char *wire_name(const wire_t *self);
const char *wire_node_name(const wire_t *self);

void wire_free_from_node(wire_t *self);

void wire_print_left(const wire_t *self);
void wire_print_right(const wire_t *self);
void wire_print(const wire_t *self);
