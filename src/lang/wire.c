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
wire_is_principal(const wire_t *self) {
    if (!self->node) return false;

    port_spec_t *port_spec = self->node->spec->port_specs[self->index];
    return port_spec->is_principal;
}

const char *
wire_name(const wire_t *self) {
    assert(self->node);
    port_spec_t *port_spec = self->node->spec->port_specs[self->index];
    assert(port_spec);
    return port_spec->name;
}

const char *
wire_node_name(const wire_t *self) {
    assert(self->node);
    return self->node->spec->name;
}

void
wire_free_from_node(wire_t *self) {
    self->node = NULL;
    self->index = -1;
}

void
wire_print_left(const wire_t *self) {
    if (!self->node) {
        printf("-<");
        return;
    }

    if (wire_is_principal(self)) {
        printf("(%s)-%s!-<", wire_node_name(self), wire_name(self));
        return;
    } else {
        printf("(%s)-%s-<", wire_node_name(self), wire_name(self));
        return;
    }
}

void
wire_print_right(const wire_t *self) {
    if (!self->node) {
        printf(">-");
        return;
    }

    if (wire_is_principal(self)) {
        printf(">-%s!-(%s)", wire_name(self), wire_node_name(self));
        return;
    } else {
        printf(">-%s-(%s)", wire_name(self), wire_node_name(self));
        return;
    }
}

void
wire_print(const wire_t *self) {
    if (self->opposite_wire)
        wire_print_left(self->opposite_wire);
    wire_print_right(self);
}

void
wire_print_reverse(const wire_t *self) {
    wire_print_left(self);
    if (self->opposite_wire)
        wire_print_right(self->opposite_wire);
}
