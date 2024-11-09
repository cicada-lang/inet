#pragma once

struct port_spec_t {
    char *name;
    bool is_principal;
};

port_spec_t *port_spec_new(const char *name, bool is_principal);
void port_spec_destroy(port_spec_t **self_pointer);
