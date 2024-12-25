#include "index.h"

lexer_t *
lexer_new(void) {
    lexer_t *self = new(lexer_t);
    self->cursor = 0;
    self->buffer_length = 0;
    self->buffer = allocate(MAX_TOKEN_LENGTH + 1);
    return self;
}

void
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
is_finished(lexer_t *self) {
    return self->cursor == self->length;
}

static char
current_char(const lexer_t *self) {
    return self->string[self->cursor];
}

static void
collect_char(lexer_t *self, char c) {
    self->buffer[self->buffer_length] = c;
    self->buffer[self->buffer_length + 1] = '\0';
    self->buffer_length++;
    assert(self->buffer_length <= MAX_TOKEN_LENGTH);
}

// dispatch over current char in a loop.

static void ignore_space(lexer_t *self);
static void ignore_comment(lexer_t *self);
static void collect_word(lexer_t *self);

void
lexer_step(lexer_t *self) {
    char c = current_char(self);
    if (c == '\0') {
        return;
    } else if (isspace(c)) {
        ignore_space(self);
    } else if (self->line_comment_start &&
               string_starts_with(
                   self->string + self->cursor,
                   self->line_comment_start)
        ) {
        ignore_comment(self);
    } else {
        collect_word(self);
    }
}

void
lexer_run(lexer_t *self) {
    assert(self->string);

    self->cursor = 0;
    self->buffer_length = 0;
    self->length = strlen(self->string);
    self->token_list = list_new_with((destroy_fn_t *) token_destroy);

    while (!is_finished(self)) {
        lexer_step(self);
    }
}

void
ignore_space(lexer_t *self) {
    while (!is_finished(self)) {
        char c = current_char(self);

        if (isspace(c)) {
            self->cursor++;
        } else {
            return;
        }
    }
}

void
ignore_comment(lexer_t *self) {
    self->cursor += strlen(self->line_comment_start);

    while (!is_finished(self)) {
        char c = current_char(self);

        if (c == '\n') {
            self->cursor++;
            return;
        } else {
            self->cursor++;
        }
    }
}

void
collect_word(lexer_t *self) {
    while (true) {
        char c = current_char(self);

        if (isspace(c) || is_finished(self)) {
            size_t start = self->cursor;
            size_t end = self->cursor + strlen(self->buffer);
            char *string = string_copy(self->buffer);
            token_t *token = token_new(string, start, end);
            list_push(self->token_list, token);
            self->buffer[0] = '\0';
            self->buffer_length = 0;
            return;
        } else {
            collect_char(self, c);
            self->cursor++;
        }
    }
}
