#include "index.h"

#define BUFFER_MAX_LENGTH 1024

lexer_t *
lexer_new(const char *text) {
    lexer_t *self = allocate(sizeof(lexer_t));
    self->token_list = list_new();
    self->text = text;
    self->text_length = strlen(text);
    self->cursor = 0;
    self->buffer = allocate(BUFFER_MAX_LENGTH + 1);
    return self;
}

void
lexer_destroy(lexer_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        lexer_t *self = *self_pointer;
        list_destroy(&self->token_list);
        free(self->buffer);
        free(self);
        *self_pointer = NULL;
    }
}
