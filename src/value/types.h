#pragma once

typedef void *value_t;

// value = higher 61 bits data + lower 3 bits tag.
// thus we have 8 tags.

#define DATA_MASK ((uint64_t) 0xfffffffffffffff8)
#define TAG_MASK ((uint64_t) 0x07)

// xobject is 8 bytes aligned.
// xaddress is not (thus need shift).

// TODO maybe this is wrong,
// object should not be c pointer,
// but be index to `vm->ram`.

typedef enum {
    XOBJECT      = 0, // 0b000
    // TODO      = 1, // 0b001
    XINT         = 2, // 0b010
    XFLOAT       = 3, // 0b011
    // TODO      = 4, // 0b100
    // TODO      = 5, // 0b101
    // TODO      = 6, // 0b110
    XEXTENDED    = 7, // 0b111
} tag_t;
