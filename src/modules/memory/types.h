#pragma once

typedef void (destructor_t)(void **item_pointer);
typedef int (comparator_t)(const void *item1, const void *item2);
