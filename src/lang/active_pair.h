#pragma once

// `active_pair_t` does NOT own `first_port` and `second_port`.

struct active_pair_t {
    port_t *first_port;
    port_t *second_port;
};

active_pair_t *active_pair_new(void);
void active_pair_destroy(active_pair_t **self_pointer);
