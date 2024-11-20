#pragma once

struct wire_t {
    node_t *node;
    port_index_t index;
    wire_t *opposite_wire;
};

wire_t *wire_new(void);
void wire_destroy(wire_t **self_pointer);

const char *wire_name(const wire_t *self);
const char *wire_node_name(const wire_t *self);

void wire_free_from_node(wire_t *self);

bool wire_is_free(const wire_t *self);
bool wire_is_principal(const wire_t *self);

wire_t *wire_connect(wire_t *first_wire, wire_t *second_wire);

void wire_print_left(const wire_t *self, file_t *file);
void wire_print_right(const wire_t *self, file_t *file);
void wire_print(const wire_t *self, file_t *file);
void wire_print_reverse(const wire_t *self, file_t *file);

void wire_print_net(wire_t *self, file_t *file);
