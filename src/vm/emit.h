#pragma once

void emit_call(const mod_t *mod, function_t *function, const char *name);
void emit_connect(const mod_t *mod, function_t *function);
void emit_use_free_wire(const mod_t *mod, function_t *function, const char *node_name, const char *port_name);
void emit_reconnect_free_wire(const mod_t *mod, function_t *function, const char *node_name, const char *port_name);
