#pragma once

port_spec_t *port_spec_new(const char *name, bool is_principal);
void port_spec_destroy(port_spec_t **self_pointer);

const char *port_spec_name(port_spec_t *self);
