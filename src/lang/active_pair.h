#pragma once

// `active_pair_t` does NOT own `first_wire` and `second_wire`.

struct active_pair_t {
    wire_t *first_wire;
    wire_t *second_wire;
};

active_pair_t *active_pair_new(void);
void active_pair_destroy(active_pair_t **self_pointer);
