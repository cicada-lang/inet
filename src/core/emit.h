#pragma once

void emit_call(const mod_t *mod, program_t *program, const char *name);
void emit_connect(const mod_t *mod, program_t *program);
void emit_use_free_wire(const mod_t *mod, program_t *program, const char *node_name, const char *port_name);
void emit_reconnect_free_wire(const mod_t *mod, program_t *program, const char *node_name, const char *port_name);
