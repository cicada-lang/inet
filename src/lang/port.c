#include "index.h"

port_t *
port_new(void) {
    port_t *self = allocate(sizeof(port_t));
    self->node = NULL;
    self->index = -1;
    self->opposite_port = NULL;
    return self;
}

void
port_destroy(port_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        port_t *self = *self_pointer;
        free(self);
        *self_pointer = NULL;
    }
}

bool
port_is_principal(port_t *self) {
    port_spec_t *port_spec = self->node->spec->port_specs[self->index];
    return port_spec->is_principal;
}

const char *
port_name(const port_t *self) {
    assert(self->node);
    assert(self->node->spec);
    port_spec_t *port_spec = self->node->spec->port_specs[self->index];
    assert(port_spec);
    assert(port_spec->name);
    return port_spec->name;
}

const char *
port_node_name(const port_t *self) {
    assert(self->node);
    assert(self->node->spec);
    assert(self->node->spec->name);
    return self->node->spec->name;
}

void
port_free_from_node(port_t *self) {
    self->node = NULL;
    self->index = -1;
}

void
port_print(const port_t *self) {
    if (self->opposite_port && self->node) {
        assert(self->opposite_port->node);
        printf("(%s)-%s:%s-(%s)",
               port_node_name(self->opposite_port),
               port_name(self->opposite_port),
               port_name(self),
               port_node_name(self));
    }

    if (self->opposite_port && !self->node) {
        assert(self->opposite_port->node);
        printf("(%s)-%s~",
               port_node_name(self->opposite_port),
               port_name(self->opposite_port));
    }

    if (!self->opposite_port && self->node) {
        printf("~%s-(%s)",
               port_name(self),
               port_node_name(self));
    }

    if (!self->opposite_port && !self->node) {
        printf("~<loss-port>~");
    }
}
