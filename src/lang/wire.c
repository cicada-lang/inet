#include "index.h"

wire_t *
wire_new(void) {
    wire_t *self = allocate(sizeof(wire_t));
    self->node = NULL;
    self->index = -1;
    self->opposite_wire = NULL;
    return self;
}

void
wire_destroy(wire_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        wire_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

bool
wire_is_principal(wire_t *self) {
    port_spec_t *port_spec = self->node->spec->port_specs[self->index];
    return port_spec->is_principal;
}

const char *
wire_name(const wire_t *self) {
    assert(self->node);
    assert(self->node->spec);
    port_spec_t *port_spec = self->node->spec->port_specs[self->index];
    assert(port_spec);
    assert(port_spec->name);
    return port_spec->name;
}

const char *
wire_node_name(const wire_t *self) {
    assert(self->node);
    assert(self->node->spec);
    assert(self->node->spec->name);
    return self->node->spec->name;
}

void
wire_free_from_node(wire_t *self) {
    self->node = NULL;
    self->index = -1;
}

void
wire_print_left(const wire_t *self) {
    if (self->node) {
        printf("(%s)-%s-<", wire_node_name(self), wire_name(self));
    } else {
        printf("-<");
    }
}

void
wire_print_right(const wire_t *self) {
    if (self->node) {
        printf(">-%s-(%s)", wire_name(self), wire_node_name(self));
    } else {
        printf(">-");
    }
}

void
wire_print(const wire_t *self) {
    if (self->opposite_wire)
        wire_print_left(self->opposite_wire);
    wire_print_right(self);
}
