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
    self->enable_int = false;
    self->enable_float = false;
    self->enable_string = false;
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

static bool
collect_string(lexer_t *self) {
    if (current_char(self) != '\"')
        return false;

    self->buffer[0] = '\0';
    self->buffer_length = 0;

    step(self);

    while (true) {
        if (is_finished(self)) {
            assert(false && "double qouted string mismatch");
        }

        char c = current_char(self);

        if (c == '\\') {
            step(self);

            char c = current_char(self);

            // escape char from: https://www.json.org/json-en.html
            if (c == 'n') collect_char(self, '\n');
            else if (c == 't') collect_char(self, '\t');
            else if (c == 'b') collect_char(self, '\b');
            else if (c == 'f') collect_char(self, '\f');
            else if (c == 'r') collect_char(self, '\r');
            else if (c == '0') collect_char(self, '\0');
            else if (c == '"') collect_char(self, '\"');
            else if (c == '\\') collect_char(self, '\\');
            else assert(false && "unknown escape char");

            step(self);
            continue;
        }

        if (c == '\"') {
            size_t end = self->cursor;
            size_t start = end - string_length(self->buffer);
            char *string = string_copy(self->buffer);
            token_t *token = token_new(
                string,
                STRING_TOKEN,
                start, end,
                self->lineno,
                self->column);
            list_push(self->token_list, token);

            self->buffer[0] = '\0';
            self->buffer_length = 0;

            step(self);
            return true;
        }

        collect_char(self, c);
        step(self);
    }
}

static void
collect_generic(lexer_t *self) {
    self->buffer[0] = '\0';
    self->buffer_length = 0;

    while (true) {
        char c = current_char(self);

        if (isspace(c) || match_delimiter(self) || is_finished(self)) {
            size_t end = self->cursor;
            size_t start = end - string_length(self->buffer);
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
        }

        collect_char(self, c);
        step(self);
    }
}

void
lexer_step(lexer_t *self) {
    if (ignore_space(self)) return;
    if (ignore_comment(self)) return;
    if (collect_delimiter(self)) return;
    if (self->enable_string && collect_string(self)) return;

    collect_generic(self);
}

static void
postprocess_int(lexer_t *self) {
    token_t *token = list_first(self->token_list);
    while (token) {
        if (token->kind == GENERIC_TOKEN && string_is_xint(token->string)) {
            token->kind = INT_TOKEN;
            token->int_value = string_parse_xint(token->string);
        }

        token = list_next(self->token_list);
    }
}

static void
postprocess_float(lexer_t *self) {
    token_t *token = list_first(self->token_list);
    while (token) {
        if (token->kind == GENERIC_TOKEN && string_is_double(token->string)) {
            token->kind = FLOAT_TOKEN;
            token->float_value = string_parse_double(token->string);
        }

        token = list_next(self->token_list);
    }
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

    if (self->enable_int)
        postprocess_int(self);

    if (self->enable_float)
        postprocess_float(self);
}
