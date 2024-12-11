#include "index.h"

wire_t *
wire_new(void) {
    wire_t *self = new(wire_t);
    self->node = NULL;
    self->index = -1;
    self->opposite = NULL;
    return self;
}

void
wire_destroy(wire_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        wire_t *self = *self_pointer;
        free(self);
        // Does NOT own `node` and `opposite`.
        *self_pointer = NULL;
    }
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

bool
wire_is_free(const wire_t *self) {
    if (self->node) return false;

    assert(self->index == -1);
    return true;
}

bool
wire_is_principal(const wire_t *self) {
    if (!self->node) return false;

    port_spec_t *port_spec = self->node->spec->port_specs[self->index];
    return port_spec->is_principal;
}

wire_t *
wire_connect(wire_t *first_wire, wire_t *second_wire) {
    wire_t *first_opposite = first_wire->opposite;
    wire_t *second_opposite = second_wire->opposite;

    first_opposite->opposite = second_opposite;
    second_opposite->opposite = first_opposite;

    wire_destroy(&first_wire);
    wire_destroy(&second_wire);

    return first_opposite;
}

void
wire_print_left(const wire_t *self, file_t *file) {
    if (!self->node) {
        fprintf(file, "-<");
        return;
    }

    node_print(self->node, file);

    if (wire_is_principal(self)) {
        fprintf(file, "-%s!-<", wire_name(self));
    } else {
        fprintf(file, "-%s-<", wire_name(self));
    }
}

void
wire_print_right(const wire_t *self, file_t *file) {
    if (!self->node) {
        fprintf(file, ">-");
        return;
    }

    if (wire_is_principal(self)) {
        fprintf(file, ">-!%s-", wire_name(self));
    } else {
        fprintf(file, ">-%s-", wire_name(self));
    }

    node_print(self->node, file);
}

void
wire_print(const wire_t *self, file_t *file) {
    if (self->opposite)
        wire_print_left(self->opposite, file);
    wire_print_right(self, file);
}

void
wire_print_reverse(const wire_t *self, file_t *file) {
    wire_print_left(self, file);
    if (self->opposite)
        wire_print_right(self->opposite, file);
}

void
wire_print_net(wire_t *self, file_t *file) {
    fprintf(file, "<net>\n");

    wire_iter_t *iter = wire_iter_new(self);
    wire_t *wire = wire_iter_start(iter);

    fprintf(file, "<root>\n");
    wire_print(wire, file);
    fprintf(file, "\n");
    fprintf(file, "</root>\n");

    wire = wire_iter_next(iter);

    fprintf(file, "<body>\n");
    while (wire) {
        wire_print(wire, file);
        fprintf(file, "\n");
        wire = wire_iter_next(iter);
    }

    wire_iter_destroy(&iter);
    fprintf(file, "</body>\n");

    fprintf(file, "</net>\n");
}
