#include "index.h"

tag_t
value_tag(value_t value) {
    return (size_t) value & TAG_MASK;
}
