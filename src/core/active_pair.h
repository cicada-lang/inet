#pragma once

struct active_pair_t {
    wire_t *first_wire;
    wire_t *second_wire;
};

active_pair_t *active_pair_new(wire_t *first_wire, wire_t *second_wire);
void active_pair_destroy(active_pair_t **self_pointer);

void active_pair_print(const active_pair_t *self);
