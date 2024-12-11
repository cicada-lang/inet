#pragma once

typedef void (destroy_t)(void **item_pointer);
typedef bool (equal_t)(const void *item1, const void *item2);
