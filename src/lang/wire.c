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

void
wire_print_left(const wire_t *self) {
    if (!self->node) {
        printf("-<");
        return;
    }

    char *node_id_string = uint_to_subscript(self->node->id);

    if (wire_is_principal(self)) {
        printf("(%s%s)-%s!-<",
               wire_node_name(self),
               node_id_string,
               wire_name(self));
    } else {
        printf("(%s%s)-%s-<",
               wire_node_name(self),
               node_id_string,
               wire_name(self));
    }

    free(node_id_string);
}

void
wire_print_right(const wire_t *self) {
    if (!self->node) {
        printf(">-");
        return;
    }

    char *node_id_string = uint_to_subscript(self->node->id);

    if (wire_is_principal(self)) {
        printf(">-!%s-(%s%s)",
               wire_name(self),
               wire_node_name(self),
               node_id_string);
    } else {
        printf(">-%s-(%s%s)",
               wire_name(self),
               wire_node_name(self),
               node_id_string);
    }

    free(node_id_string);
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

void
wire_inspect(wire_t *self) {
    printf("<net>\n");

    printf("<root>\n");
    wire_print(self);
    printf("\n");
    printf("</root>\n");

    printf("<body>\n");
    list_t *occurred_wire_list = list_new();
    list_t *occurred_node_list = list_new();
    list_t *remaining_node_list = list_new();

    list_push(occurred_wire_list, self);
    if (self->opposite_wire)
        list_push(occurred_wire_list, self->opposite_wire);

    if (self->opposite_wire && self->opposite_wire->node)
        list_push(remaining_node_list, self->opposite_wire->node);

    node_t *node = list_pop(remaining_node_list);
    while (node) {
        if (list_has(occurred_wire_list, node)) continue;

        list_push(occurred_wire_list, node);
        for (port_index_t i = 0; i < node->spec->arity; i++) {
            wire_t *wire = node->wires[i];
            if (wire->opposite_wire) {
                if (list_has(occurred_wire_list, wire)) continue;
                if (list_has(occurred_wire_list, wire->opposite_wire)) continue;

                wire_print(wire);
                printf("\n");

                list_push(occurred_wire_list, wire);
                list_push(occurred_wire_list, wire->opposite_wire);
            } else {
                if (list_has(occurred_wire_list, wire)) continue;

                wire_print(wire);
                printf("\n");

                list_push(occurred_wire_list, wire);
            }

            if (wire->opposite_wire)
                list_push(remaining_node_list, wire->opposite_wire->node);
        }

        node = list_pop(remaining_node_list);
    }

    list_destroy(&occurred_wire_list);
    list_destroy(&occurred_node_list);
    list_destroy(&remaining_node_list);

    printf("</body>\n");

    printf("</net>\n");

}
