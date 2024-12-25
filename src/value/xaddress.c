#include "index.h"

value_t
xaddress(size_t address) {
    return (value_t) ((address << 3) | XADDRESS);
}

bool
is_xaddress(value_t value) {
    return value_tag(value) == XADDRESS;
}

size_t
to_address(value_t value) {
    assert(is_xaddress(value));
    return ((uint64_t) value) >> 3;
}
