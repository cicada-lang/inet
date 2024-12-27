#include "index.h"

static port_def_t *
compile_port_def(const char *word) {
    if (string_ends_with(word, "!")) {
        word = string_slice(word, 0, strlen(word) - 1);
        return port_def_new(word, true);
    } else {
        return port_def_new(word, false);
    }
}

void
interpret_stmt(vm_t *vm, stmt_t *unknown_stmt) {
    switch (unknown_stmt->kind) {
    case DEFINE_NODE_STMT: {
        define_node_stmt_t *stmt = (define_node_stmt_t *)unknown_stmt;
        check_name_not_defined(vm, stmt->name, stmt->head_token);

        def_t *def =
            def_from_node_def(node_def_new(
                stmt->name,
                list_length(stmt->input_token_list),
                list_length(stmt->output_token_list)));

        port_index_t index = 0;

        token_t *input_token = list_first(stmt->input_token_list);
        while (input_token) {
            def->as_node_def->port_defs[index] = compile_port_def(input_token->string);
            input_token = list_next(stmt->input_token_list);
            index++;
        }

        token_t *output_token = list_first(stmt->output_token_list);
        while (output_token) {
            def->as_node_def->port_defs[index] = compile_port_def(output_token->string);
            output_token = list_next(stmt->output_token_list);
            index++;
        }

        mod_define(vm->mod, def);
        return;
    }

    case DEFINE_RULE_STMT: {
        define_rule_stmt_t *stmt = (define_rule_stmt_t *)unknown_stmt;
        program_t *program = compile(vm, stmt->token_list);
        check_node_name_defined(vm, stmt->first_name, stmt->head_token);
        check_node_name_defined(vm, stmt->second_name, stmt->head_token);
        mod_define_rule(
            vm->mod,
            stmt->first_name,
            stmt->second_name,
            program);
        return;
    }

    case DEFINE_PROGRAM_STMT: {
        define_program_stmt_t *stmt = (define_program_stmt_t *)unknown_stmt;
        check_name_not_defined(vm, stmt->name, stmt->head_token);
        program_t *program = compile(vm, stmt->token_list);
        def_t *def = def_from_program_def(program_def_new(stmt->name, program));
        mod_define(vm->mod, def);
        return;
    }

    case RUN_PROGRAM_STMT: {
        run_program_stmt_t *stmt = (run_program_stmt_t *)unknown_stmt;
        program_t *program = compile(vm, stmt->token_list);
        size_t base_length = stack_length(vm->return_stack);
        stack_push(vm->return_stack, frame_new(program));
        vm_run_until(vm, base_length);
        vm_net_run(vm);
        return;
    }
    }

    assert(false);
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
