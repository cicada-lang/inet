#pragma once

typedef void (destroy_fn_t)(void **value_pointer);
typedef bool (equal_fn_t)(const void *value1, const void *value2);
typedef void *(copy_fn_t)(void *value);

