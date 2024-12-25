#pragma once

struct spec_t { const spec_tag_t tag; };

void spec_destroy(spec_t **self_pointer);

const char *spec_name(spec_t *self);
const char *spec_tag_name(spec_tag_t tag);

void spec_print(const spec_t *self, file_t *file);
