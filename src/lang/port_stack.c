#include "index.h"

struct port_stack_t {
    size_t size;
    size_t cursor;
    port_t **port;
};
