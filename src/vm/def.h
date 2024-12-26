#pragma once

struct def_t { const def_kind_t kind; };

const primitive_def_t *primitive_def_cast(const def_t *def);
const program_def_t *program_def_cast(const def_t *def);
const node_def_t *node_def_cast(const def_t *def);

void def_destroy(def_t **self_pointer);

const char *def_name(const def_t *self);
const char *def_kind_name(def_kind_t kind);

void def_print(const def_t *self, file_t *file);
