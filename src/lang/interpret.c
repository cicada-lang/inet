#include "index.h"

void
interpret_stmt(vm_t *vm, stmt_t *unknown_stmt) {
    (void) vm;
    (void) unknown_stmt;

    // TODO
}

void
interpret_mod(vm_t *vm) {
    parser_t *parser = parser_new();
    parser->lexer = lexer_new();
    parser->lexer->line_comment = "--";
    parser->src = vm->mod->src;
    parser->string = vm->mod->string;
    parser->err = vm->err;
    parser_parse(parser);

    list_t *stmt_list = parser->stmt_list;
    parser_destroy(&parser);

    stmt_t *stmt = list_first(stmt_list);
    while (stmt) {
        interpret_stmt(vm, stmt);
        stmt = list_next(stmt_list);
    }
}
