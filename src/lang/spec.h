#pragma once

struct spec_t { const spec_tag_t tag; };

void spec_destroy(spec_t **self_pointer);
