#include "index.h"

struct parser_t {
    list_t *token_list;
    list_t *stmt_list;
};

static parser_t *
parser_new(list_t *token_list) {
    parser_t *self = allocate(sizeof(parser_t));
    self->token_list = token_list;

    self->stmt_list = list_new();
    list_set_item_destructor(
        self->stmt_list,
        (list_item_destructor_t *) stmt_destroy);

    return self;
}

static void
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

static void
parser_parse(parser_t *self) {
    while (!list_is_empty(self->token_list)) {
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
            printf("[parse] unknown starting token: %s", token->string);
            assert(false);
        }
    }
}

static char *parse_node_name(const char *string) {
    assert(string_starts_with(string, "("));
    assert(string_ends_with(string, ")"));
    int i = string_find_index(string, ')');
    assert(i != -1);
    return string_slice(string, 1, i);
}

void
parser_parse_define_node_stmt(parser_t *self) {
    token_t *rune_token = list_shift(self->token_list);
    token_destroy(&rune_token);

    token_t *first_token = list_shift(self->token_list);
    assert(!token_is_rune(first_token));
    char *name = parse_node_name(first_token->string);
    token_destroy(&first_token);

    define_node_stmt_t *stmt = define_node_stmt_new(name);

    bool output_flag = false;
    while (!list_is_empty(self->token_list)) {
        token_t *token = list_shift(self->token_list);
        if (token_is_rune(token)) {
            list_unshift(self->token_list, token);
            break;
        }

        if (string_equal(token->string, "--")) {
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

static char *
parse_rule_first_name(const char *string) {
    assert(string_starts_with(string, "("));
    assert(string_ends_with(string, ")"));
    int i = string_find_index(string, ')');
    assert(i != -1);
    return string_slice(string, 1, i);
}

static char *
parse_rule_second_name(const char *string) {
    assert(string_starts_with(string, "("));
    assert(string_ends_with(string, ")"));
    int i = string_find_index(string, ')');
    assert(i != -1);
    assert(string[i+1] == '-');
    assert(string[i+2] == '(');
    return string_slice(string, i+3, strlen(string) - 1);
}

void
parser_parse_define_rule_stmt(parser_t *self) {
    token_t *rune_token = list_shift(self->token_list);
    token_destroy(&rune_token);

    token_t *first_token = list_shift(self->token_list);
    assert(!token_is_rune(first_token));
    char *first_name = parse_rule_first_name(first_token->string);
    char *second_name = parse_rule_second_name(first_token->string);
    token_destroy(&first_token);

    list_t *token_list = list_new();
    list_set_item_destructor(
        token_list,
        (list_item_destructor_t *) token_destroy);

    while (!list_is_empty(self->token_list)) {
        token_t *token = list_shift(self->token_list);
        if (token_is_rune(token)) {
            list_unshift(self->token_list, token);
            break;
        }

        list_push(token_list, token);
    }

    list_push(self->stmt_list,
              define_rule_stmt_new(
                  first_name,
                  second_name,
                  token_list));
}

void
parser_parse_define_program_stmt(parser_t *self) {
    token_t *rune_token = list_shift(self->token_list);
    token_destroy(&rune_token);

    token_t *first_token = list_shift(self->token_list);
    assert(!token_is_rune(first_token));
    char *name = string_dup(first_token->string);
    token_destroy(&first_token);

    list_t *token_list = list_new();
    list_set_item_destructor(
        token_list,
        (list_item_destructor_t *) token_destroy);

    while (!list_is_empty(self->token_list)) {
        token_t *token = list_shift(self->token_list);
        if (token_is_rune(token)) {
            list_unshift(self->token_list, token);
            break;
        }

        list_push(token_list, token);
    }

    list_push(self->stmt_list,
              define_program_stmt_new(
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

list_t *
parse(list_t *token_list) {
    parser_t *parser = parser_new(token_list);
    parser_parse(parser);
    list_t *stmt_list = parser->stmt_list;
    parser_destroy(&parser);
    return stmt_list;
}
