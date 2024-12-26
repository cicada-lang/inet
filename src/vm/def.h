#pragma once

struct def_t { const def_kind_t kind; };

void def_destroy(def_t **self_pointer);

const char *def_name(def_t *self);
const char *def_kind_name(def_kind_t kind);

void def_print(const def_t *self, file_t *file);
