#pragma once

struct port_def_t {
    char *name;
    bool is_principal;
};

port_def_t *port_def_new(const char *name, bool is_principal);
void port_def_destroy(port_def_t **self_pointer);
