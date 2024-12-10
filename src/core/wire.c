#include "index.h"

wire_t *
wire_new(void) {
    wire_t *self = new(wire_t);
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
        // Does NOT own `node` and `opposite_wire`.
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
    wire_t *first_opposite_wire = first_wire->opposite_wire;
    wire_t *second_opposite_wire = second_wire->opposite_wire;

    first_opposite_wire->opposite_wire = second_opposite_wire;
    second_opposite_wire->opposite_wire = first_opposite_wire;

    wire_destroy(&first_wire);
    wire_destroy(&second_wire);

    return first_opposite_wire;
}

void
wire_print_left(const wire_t *self, file_t *file) {
    if (!self->node) {
        fprintf(file, "-<");
        return;
    }

    char *node_id_string = uint_to_subscript(self->node->id);

    if (wire_is_principal(self)) {
        fprintf(file, "(%s%s)-%s!-<",
                wire_node_name(self),
                node_id_string,
                wire_name(self));
    } else {
        fprintf(file, "(%s%s)-%s-<",
                wire_node_name(self),
                node_id_string,
                wire_name(self));
    }

    free(node_id_string);
}

void
wire_print_right(const wire_t *self, file_t *file) {
    if (!self->node) {
        fprintf(file, ">-");
        return;
    }

    char *node_id_string = uint_to_subscript(self->node->id);

    if (wire_is_principal(self)) {
        fprintf(file, ">-!%s-(%s%s)",
                wire_name(self),
                wire_node_name(self),
                node_id_string);
    } else {
        fprintf(file, ">-%s-(%s%s)",
                wire_name(self),
                wire_node_name(self),
                node_id_string);
    }

    free(node_id_string);
}

void
wire_print(const wire_t *self, file_t *file) {
    if (self->opposite_wire)
        wire_print_left(self->opposite_wire, file);
    wire_print_right(self, file);
}

void
wire_print_reverse(const wire_t *self, file_t *file) {
    wire_print_left(self, file);
    if (self->opposite_wire)
        wire_print_right(self->opposite_wire, file);
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
    fprintf(file, "</body>\n");

    fprintf(file, "</net>\n");
}
