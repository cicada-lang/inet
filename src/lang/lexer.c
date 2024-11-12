#include "index.h"

#define BUFFER_MAX_LENGTH 1024

struct lexer_t {
    list_t *token_list;
    const char *text;
    size_t text_length;
    size_t cursor;
    char *buffer;
};

static lexer_t *
lexer_new(const char *text) {
    lexer_t *self = allocate(sizeof(lexer_t));
    self->token_list = list_new();
    self->text = text;
    self->text_length = strlen(text);
    self->cursor = 0;
    self->buffer = allocate(BUFFER_MAX_LENGTH + 1);
    return self;
}

static void
lexer_destroy(lexer_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        lexer_t *self = *self_pointer;
        // Does not own `token_list`, which is to be returned.
        free(self->buffer);
        free(self);
        *self_pointer = NULL;
    }
}

static void
lexer_lex(lexer_t *self) {
    (void) self;
    return;
}

list_t *
lex(const char *text) {
    lexer_t *lexer = lexer_new(text);
    lexer_lex(lexer);
    list_t *token_list = lexer->token_list;
    lexer_destroy(&lexer);
    return token_list;
}
