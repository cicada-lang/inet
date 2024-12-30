#include "index.h"

parser_t *
parser_new(void) {
    parser_t *self = new(parser_t);
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

static void maybe_ignore_inline_comment(parser_t *self);
static void parse_define_node_stmt(parser_t *self);
static void parse_define_rule_stmt(parser_t *self);
static void parse_define_function_stmt(parser_t *self);
static void parse_begin_function_stmt(parser_t *self);
static void parse_word(parser_t *self);

static bool
token_is_end(const token_t *token) {
    return string_equal(token->string, "end");
}

void
parser_parse(parser_t *self) {
    assert(self->string);
    assert(self->lexer);

    self->lexer->string = self->string;
    lexer_run(self->lexer);
    self->token_list = self->lexer->token_list;

    self->stmt_list = list_new_with((destroy_fn_t *) stmt_destroy);
    while (true) {
        maybe_ignore_inline_comment(self);

        if (list_is_empty(self->token_list)) break;

        token_t *token = list_first(self->token_list);
        if (string_equal(token->string, "define-node"))
            parse_define_node_stmt(self);
        else if (string_equal(token->string, "define-rule"))
            parse_define_rule_stmt(self);
        else if (string_equal(token->string, "define"))
            parse_define_function_stmt(self);
        else if (string_equal(token->string, "begin"))
            parse_begin_function_stmt(self);
        else
            parse_word(self);
    }
}

void
maybe_ignore_inline_comment(parser_t *self) {
    if (list_is_empty(self->token_list)) return;

    token_t *first_token = list_first(self->token_list);
    if (!string_equal(first_token->string, "(-")) return;

    size_t before_token_list_length = list_length(self->token_list);

    token_t *comment_start_token = list_shift(self->token_list);
    token_destroy(&comment_start_token);

    while (!list_is_empty(self->token_list)) {
        // handle nested inline comment.
        maybe_ignore_inline_comment(self);

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
        maybe_ignore_inline_comment(self);
}

void
parse_define_node_stmt(parser_t *self) {
    token_t *rune_token = list_shift(self->token_list);
    token_destroy(&rune_token);

    token_t *head_token = list_shift(self->token_list);
    char *name = head_token->string;

    define_node_stmt_t *stmt = define_node_stmt_new(head_token, name);

    bool output_flag = false;
    while (true) {
        maybe_ignore_inline_comment(self);

        if (list_is_empty(self->token_list)) break;

        token_t *token = list_shift(self->token_list);
        if (token_is_end(token))
            break;

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

void
parse_define_rule_stmt(parser_t *self) {
    token_t *rune_token = list_shift(self->token_list);
    token_destroy(&rune_token);

    token_t *first_token = list_shift(self->token_list);
    token_t *second_token = list_shift(self->token_list);

    char *first_name = first_token->string;
    char *second_name = second_token->string;

    list_t *token_list = list_new_with((destroy_fn_t *) token_destroy);
    while (true) {
        maybe_ignore_inline_comment(self);

        if (list_is_empty(self->token_list)) break;

        token_t *token = list_shift(self->token_list);
        if (token_is_end(token))
            break;

        list_push(token_list, token);
    }

    list_push(self->stmt_list,
              define_rule_stmt_new(
                  first_token,
                  first_name,
                  second_name,
                  token_list));
}

void
parse_define_function_stmt(parser_t *self) {
    token_t *rune_token = list_shift(self->token_list);
    token_destroy(&rune_token);

    token_t *head_token = list_shift(self->token_list);
    char *name = string_copy(head_token->string);

    list_t *token_list = list_new_with((destroy_fn_t *) token_destroy);
    while (!list_is_empty(self->token_list)) {
        maybe_ignore_inline_comment(self);

        token_t *token = list_shift(self->token_list);
        if (token_is_end(token))
            break;

        list_push(token_list, token);
    }

    list_push(self->stmt_list,
              define_function_stmt_new(
                  head_token,
                  name,
                  token_list));
}

void
parse_begin_function_stmt(parser_t *self) {
    token_t *rune_token = list_shift(self->token_list);
    token_destroy(&rune_token);

    list_t *token_list = list_new_with((destroy_fn_t *) token_destroy);
    while (!list_is_empty(self->token_list)) {
        maybe_ignore_inline_comment(self);

        token_t *token = list_shift(self->token_list);
        if (token_is_end(token))
            break;

        list_push(token_list, token);
    }

    list_push(self->stmt_list,
              begin_function_stmt_new(token_list));
}

void
parse_word(parser_t *self) {
    maybe_ignore_inline_comment(self);

    list_t *token_list = list_new_with((destroy_fn_t *) token_destroy);
    token_t *token = list_shift(self->token_list);
    list_push(token_list, token);
    list_push(self->stmt_list, begin_function_stmt_new(token_list));
}
