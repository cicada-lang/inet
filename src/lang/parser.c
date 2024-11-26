#include "index.h"

parser_t *
parser_new(void) {
    parser_t *self = allocate(sizeof(parser_t));
    self->token_list = NULL;
    self->err = stderr;
    return self;
}

void
parser_destroy(parser_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        parser_t *self = *self_pointer;
        list_destroy(&self->token_list);
        // keep `stmt_list` to be collected as return value.
        free(self);
        *self_pointer = NULL;
    }
}

// build `stmt_list` from `token_list`,
// dispatch by different runes in a loop.

static void parser_maybe_ignore_inline_comment(parser_t *self);
static void parser_parse_define_node_stmt(parser_t *self);
static void parser_parse_define_rule_stmt(parser_t *self);
static void parser_parse_define_program_stmt(parser_t *self);
static void parser_parse_run_program_stmt(parser_t *self);

static bool token_is_rune(const token_t *token) {
    if (string_equal(token->string, "*"))
        return true;
    else if (string_equal(token->string, "!"))
        return true;
    else if (string_equal(token->string, "="))
        return true;
    else if (string_equal(token->string, "."))
        return true;
    else
        return false;
}

void
parser_parse(parser_t *self) {
    assert(self->text);
    assert(self->lexer);

    self->lexer->text = self->text;
    lexer_lex(self->lexer);
    self->token_list = self->lexer->token_list;

    self->stmt_list = list_new();
    list_set_item_destructor(
        self->stmt_list,
        (list_item_destructor_t *) stmt_destroy);

    while (true) {
        parser_maybe_ignore_inline_comment(self);

        if (list_is_empty(self->token_list)) break;

        token_t *token = list_first(self->token_list);
        if (string_equal(token->string, "*"))
            parser_parse_define_node_stmt(self);
        else if (string_equal(token->string, "!"))
            parser_parse_define_rule_stmt(self);
        else if (string_equal(token->string, "="))
            parser_parse_define_program_stmt(self);
        else if (string_equal(token->string, "."))
            parser_parse_run_program_stmt(self);
        else {
            fprintf(self->err, "[parser-error] unknown starting token: %s\n", token->string);
            fprintf(self->err, "[src] %s\n", self->src);
            text_print_context(self->err, self->text, token->start, token->end);
            exit(1);
        }
    }
}

void
parser_maybe_ignore_inline_comment(parser_t *self) {
    if (list_is_empty(self->token_list)) return;

    token_t *first_token = list_first(self->token_list);
    if (!string_equal(first_token->string, "(-")) return;

    size_t before_token_list_length = list_length(self->token_list);

    token_t *comment_start_token = list_shift(self->token_list);
    token_destroy(&comment_start_token);

    while (!list_is_empty(self->token_list)) {
        // handle nested inline comment.
        parser_maybe_ignore_inline_comment(self);

        token_t *token = list_shift(self->token_list);
        if (string_equal(token->string, "-)")) {
            token_destroy(&token);
            break;
        } else {
            token_destroy(&token);
        }
    }

    // handle consecutive inline comment.
    if (list_length(self->token_list) < before_token_list_length)
        parser_maybe_ignore_inline_comment(self);
}

static void
check_node_name_format(parser_t *self, const token_t *token) {
    char *string = token->string;

    if (!(string_starts_with(string, "(") &&
          string_ends_with(string, ")") &&
          string_count_char(string, '(') == 1 &&
          string_count_char(string, ')') == 1))
    {
        fprintf(self->err, "[parser-error] a node name must be like (<name>)\n");
        fprintf(self->err, "[src] %s\n", self->src);
        text_print_context(self->err, self->text, token->start, token->end);
        exit(1);
    }
}

static char *
parse_node_name(parser_t *self, const token_t *token) {
    check_node_name_format(self, token);
    int i = string_find_index(token->string, ')');
    return string_slice(token->string, 1, i);
}

void
parser_parse_define_node_stmt(parser_t *self) {
    token_t *rune_token = list_shift(self->token_list);
    token_destroy(&rune_token);

    token_t *head_token = list_shift(self->token_list);
    char *name = parse_node_name(self, head_token);

    define_node_stmt_t *stmt = define_node_stmt_new(head_token, name);

    bool output_flag = false;
    while (true) {
        parser_maybe_ignore_inline_comment(self);

        if (list_is_empty(self->token_list)) break;

        token_t *token = list_shift(self->token_list);
        if (token_is_rune(token)) {
            list_unshift(self->token_list, token);
            break;
        }

        if (string_equal(token->string, "->")) {
            output_flag = true;
            token_destroy(&token);
            continue;
        }

        if (output_flag) {
            list_push(stmt->output_token_list, token);
        } else {
            list_push(stmt->input_token_list, token);
        }
    }

    list_push(self->stmt_list, stmt);
}

static void
check_rule_name_format(parser_t *self, const token_t *token) {
    char *string = token->string;

    if (!(string_starts_with(string, "(") &&
          string_ends_with(string, ")") &&
          string_count_char(string, '(') == 2 &&
          string_count_char(string, ')') == 2 &&
          string_count_substring(string, ")-(") == 1))
    {
        fprintf(self->err, "[parser-error] a rule name must be like (<name>)-(<name>)\n");
        fprintf(self->err, "[src] %s\n", self->src);
        text_print_context(self->err, self->text, token->start, token->end);
        exit(1);
    }
}

static char *
parse_rule_first_name(parser_t *self, const token_t *token) {
    check_rule_name_format(self, token);
    int i = string_find_index(token->string, ')');
    return string_slice(token->string, 1, i);
}

static char *
parse_rule_second_name(parser_t *self, const token_t *token) {
    check_rule_name_format(self, token);
    int i = string_find_index(token->string, ')');
    return string_slice(token->string, i+3, strlen(token->string) - 1);
}

void
parser_parse_define_rule_stmt(parser_t *self) {
    token_t *rune_token = list_shift(self->token_list);
    token_destroy(&rune_token);

    token_t *head_token = list_shift(self->token_list);
    char *first_name = parse_rule_first_name(self, head_token);
    char *second_name = parse_rule_second_name(self, head_token);

    list_t *token_list = list_new();
    list_set_item_destructor(
        token_list,
        (list_item_destructor_t *) token_destroy);

    while (true) {
        parser_maybe_ignore_inline_comment(self);

        if (list_is_empty(self->token_list)) break;

        token_t *token = list_shift(self->token_list);
        if (token_is_rune(token)) {
            list_unshift(self->token_list, token);
            break;
        }

        list_push(token_list, token);
    }

    list_push(self->stmt_list,
              define_rule_stmt_new(
                  head_token,
                  first_name,
                  second_name,
                  token_list));
}

static void
check_program_name_format(parser_t *self, const token_t *token) {
    char *string = token->string;

    if (token_is_rune(token)) {
        fprintf(self->err, "[parser-error] program name can not be a rune: %s\n", string);
        fprintf(self->err, "[src] %s\n", self->src);
        text_print_context(self->err, self->text, token->start, token->end);
        exit(1);
    }

    if (string_has_char(string, '{') ||
        string_has_char(string, '}') ||
        string_has_char(string, '[') ||
        string_has_char(string, ']') ||
        string_has_char(string, '(') ||
        string_has_char(string, ')'))
    {
        fprintf(self->err, "[parser-error] invalid program name: %s\n", string);
        fprintf(self->err, "[src] %s\n", self->src);
        text_print_context(self->err, self->text, token->start, token->end);
        exit(1);
    }
}

void
parser_parse_define_program_stmt(parser_t *self) {
    token_t *rune_token = list_shift(self->token_list);
    token_destroy(&rune_token);

    token_t *head_token = list_shift(self->token_list);
    check_program_name_format(self, head_token);
    char *name = string_dup(head_token->string);

    list_t *token_list = list_new();
    list_set_item_destructor(
        token_list,
        (list_item_destructor_t *) token_destroy);

    while (!list_is_empty(self->token_list)) {
        parser_maybe_ignore_inline_comment(self);

        token_t *token = list_shift(self->token_list);
        if (token_is_rune(token)) {
            list_unshift(self->token_list, token);
            break;
        }

        list_push(token_list, token);
    }

    list_push(self->stmt_list,
              define_program_stmt_new(
                  head_token,
                  name,
                  token_list));
}

void
parser_parse_run_program_stmt(parser_t *self) {
    token_t *rune_token = list_shift(self->token_list);
    token_destroy(&rune_token);

    list_t *token_list = list_new();
    list_set_item_destructor(
        token_list,
        (list_item_destructor_t *) token_destroy);

    while (!list_is_empty(self->token_list)) {
        parser_maybe_ignore_inline_comment(self);

        token_t *token = list_shift(self->token_list);
        if (token_is_rune(token)) {
            list_unshift(self->token_list, token);
            break;
        }

        list_push(token_list, token);
    }

    list_push(self->stmt_list,
              run_program_stmt_new(token_list));
}
