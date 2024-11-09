#pragma once

void *allocate(size_t size);
void *allocate_many(size_t size, size_t unit_size);
void *allocate_pointer_array(size_t size);
