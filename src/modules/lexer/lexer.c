#include "index.h"

static void
lexer_init(lexer_t *self) {
    self->cursor = 0;
    self->lineno = 1;
    self->column = 1;
    self->buffer_length = 0;
}

lexer_t *
lexer_new(void) {
    lexer_t *self = new(lexer_t);
    self->buffer = allocate(MAX_TOKEN_LENGTH + 1);
    self->delimiter_list = list_new();
    lexer_init(self);
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

void
lexer_add_delimiter(lexer_t *self, const char *delimiter) {
    list_push(self->delimiter_list, (void *) delimiter);
}

static bool
is_finished(lexer_t *self) {
    return self->cursor == self->length;
}

static char
current_char(const lexer_t *self) {
    return self->string[self->cursor];
}

static const char*
current_substring(const lexer_t *self) {
    return self->string + self->cursor;
}

static const char*
match_delimiter(const lexer_t *self) {
    const char *delimiter = list_first(self->delimiter_list);
    while (delimiter) {
        if (string_starts_with(current_substring(self), delimiter))
            return delimiter;

        delimiter = list_next(self->delimiter_list);
    }

    return NULL;
}

static void
step(lexer_t *self) {
    assert(!is_finished(self));

    if (current_char(self) == '\n') {
        self->lineno++;
        self->column = 1;
    } else {
        self->column++;
    }

    self->cursor++;
}

static void
forward(lexer_t *self, size_t length) {
    while (length > 0) {
        step(self);
        length--;
    }
}

static bool
ignore_space(lexer_t *self) {
    char c = current_char(self);
    if (!isspace(c))
        return false;

    while (!is_finished(self)) {
        char c = current_char(self);

        if (isspace(c)) {
            step(self);
        } else {
            break;
        }
    }

    return true;
}

static bool
ignore_comment(lexer_t *self) {
    if (!self->line_comment)
        return false;

    if (!string_starts_with(current_substring(self), self->line_comment))
        return false;

    forward(self, string_length(self->line_comment));

    while (!is_finished(self)) {
        char c = current_char(self);

        if (c == '\n') {
            step(self);
            break;
        } else {
            step(self);
        }
    }

    return true;
}

static bool
collect_delimiter(lexer_t *self) {
    const char *delimiter = match_delimiter(self);
    if (!delimiter)
        return false;

    size_t start = self->cursor;
    size_t end = self->cursor + string_length(delimiter);

    forward(self, string_length(delimiter));

    char *string = string_copy(delimiter);
    token_t *token = token_new(
        string,
        DELIMITER_TOKEN,
        start, end,
        self->lineno,
        self->column);
    list_push(self->token_list, token);

    return true;
}

static void
collect_char(lexer_t *self, char c) {
    self->buffer[self->buffer_length] = c;
    self->buffer[self->buffer_length + 1] = '\0';
    self->buffer_length++;
    assert(self->buffer_length <= MAX_TOKEN_LENGTH);
}

static void
collect_generic(lexer_t *self) {
    self->buffer[0] = '\0';
    self->buffer_length = 0;

    while (true) {
        char c = current_char(self);

        if (isspace(c) || match_delimiter(self) || is_finished(self)) {
            size_t start = self->cursor;
            size_t end = self->cursor + string_length(self->buffer);
            char *string = string_copy(self->buffer);
            token_t *token = token_new(
                string,
                GENERIC_TOKEN,
                start, end,
                self->lineno,
                self->column);
            list_push(self->token_list, token);

            self->buffer[0] = '\0';
            self->buffer_length = 0;
            return;
        } else {
            collect_char(self, c);
            step(self);
        }
    }
}

void
lexer_step(lexer_t *self) {
    if (ignore_space(self)) return;
    if (ignore_comment(self)) return;
    if (collect_delimiter(self)) return;

    collect_generic(self);
}

void
lexer_run(lexer_t *self) {
    assert(self->string);

    lexer_init(self);

    self->length = string_length(self->string);
    self->token_list = list_new_with((destroy_fn_t *) token_destroy);

    while (!is_finished(self)) {
        lexer_step(self);
    }
}
