#include "index.h"

port_def_t *
port_def_new(const char *name, bool is_principal) {
    port_def_t *self = new(port_def_t);
    self->name = string_copy(name);
    self->is_principal = is_principal;
    return self;
}

void
port_def_destroy(port_def_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        port_def_t *self = *self_pointer;
        free(self->name);
        free(self);
        *self_pointer = NULL;
    }
}

port_def_t *
port_def_from_string(const char *string) {
    if (string_ends_with(string, "!")) {
        string = string_slice(string, 0, string_length(string) - 1);
        return port_def_new(string, true);
    } else {
        return port_def_new(string, false);
    }
}
