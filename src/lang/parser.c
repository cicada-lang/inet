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

void
parser_parse_define_node_stmt(parser_t *self) {
    (void) self;
}

void
parser_parse_define_rule_stmt(parser_t *self) {
    (void) self;
}

void
parser_parse_define_program_stmt(parser_t *self) {
    (void) self;
}

void
parser_parse_run_program_stmt(parser_t *self) {
    (void) self;
}

list_t *
parse(list_t *token_list) {
    parser_t *parser = parser_new(token_list);
    parser_parse(parser);
    list_t *stmt_list = parser->stmt_list;
    parser_destroy(&parser);
    return stmt_list;
}
