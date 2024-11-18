#include "index.h"

#define MAX_BUFFER_LENGTH 1024

struct lexer_t {
    const char *text;
    size_t text_length;
    size_t cursor;
    char *buffer;
    size_t buffer_length;
    list_t *token_list;
};

static lexer_t *
lexer_new(const char *text) {
    lexer_t *self = allocate(sizeof(lexer_t));
    self->text = text;
    self->text_length = strlen(text);
    self->cursor = 0;
    self->buffer = allocate(MAX_BUFFER_LENGTH + 1);
    self->buffer_length = 0;
    self->token_list = list_new();
    return self;
}

static void
lexer_destroy(lexer_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        lexer_t *self = *self_pointer;
        // keep `token_list` to be collected as return value.
        free(self->buffer);
        free(self);
        *self_pointer = NULL;
    }
}

static bool
lexer_is_finished(lexer_t *self) {
    return self->cursor == self->text_length;
}

static char
lexer_current_char(const lexer_t *self) {
    return self->text[self->cursor];
}

static void
lexer_collect_char(lexer_t *self, char c) {
    self->buffer[self->buffer_length] = c;
    self->buffer[self->buffer_length + 1] = '\0';
    self->buffer_length++;
    assert(self->buffer_length <= MAX_BUFFER_LENGTH);
}

// dispatch over current char in a loop.

static void lexer_lex_ignore_space(lexer_t *self);
static void lexer_lex_word(lexer_t *self);

static void
lexer_lex(lexer_t *self) {
    while (!lexer_is_finished(self)) {
        char c = lexer_current_char(self);
        if (c == '\0')
            return;
        else if (isspace(c))
            lexer_lex_ignore_space(self);
        else
            lexer_lex_word(self);
    }
}

void
lexer_lex_ignore_space(lexer_t *self) {
    while (!lexer_is_finished(self)) {
        char c = lexer_current_char(self);

        if (isspace(c))
            self->cursor++;
        else
            return;
    }
}

void
lexer_lex_word(lexer_t *self) {
    while (true) {
        char c = lexer_current_char(self);

        if (isspace(c) || lexer_is_finished(self)) {
            size_t start = self->cursor;
            size_t end = self->cursor + strlen(self->buffer);
            char *string = string_dup(self->buffer);
            token_t *token = token_new(string, start, end);
            list_push(self->token_list, token);
            self->buffer[0] = '\0';
            self->buffer_length = 0;
            return;
        } else {
            lexer_collect_char(self, c);
            self->cursor++;
        }
    }
}


list_t *
lex(const char *text) {
    lexer_t *lexer = lexer_new(text);
    lexer_lex(lexer);
    list_t *token_list = lexer->token_list;
    lexer_destroy(&lexer);
    return token_list;
}
