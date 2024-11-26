#include "index.h"

static port_spec_t *
compile_port_spec(const char *word) {
    if (string_ends_with(word, "!")) {
        word = string_slice(word, 0, strlen(word) - 1);
        return port_spec_new(word, true);
    } else {
        return port_spec_new(word, false);
    }
}

void
interpret_stmt(worker_t *worker, stmt_t *unknown_stmt) {
    switch (unknown_stmt->tag) {
    case DEFINE_NODE_STMT: {
        define_node_stmt_t *stmt = (define_node_stmt_t *)unknown_stmt;
        check_name_not_defined(worker, stmt->name, stmt->head_token);

        node_spec_t *spec =
            node_spec_new(
                stmt->name,
                list_length(stmt->input_token_list),
                list_length(stmt->output_token_list));

        port_index_t index = 0;

        token_t *input_token = list_start(stmt->input_token_list);
        while (input_token) {
            spec->port_specs[index] = compile_port_spec(input_token->string);
            input_token = list_next(stmt->input_token_list);
            index++;
        }

        token_t *output_token = list_start(stmt->output_token_list);
        while (output_token) {
            spec->port_specs[index] = compile_port_spec(output_token->string);
            output_token = list_next(stmt->output_token_list);
            index++;
        }

        mod_define(worker->mod, (spec_t *) spec);
        return;
    }

    case DEFINE_RULE_STMT: {
        define_rule_stmt_t *stmt = (define_rule_stmt_t *)unknown_stmt;
        program_t *program = compile(worker, stmt->token_list);
        check_node_name_defined(worker, stmt->first_name, stmt->head_token);
        check_node_name_defined(worker, stmt->second_name, stmt->head_token);
        mod_define_rule(
            worker->mod,
            stmt->first_name,
            stmt->second_name,
            program);
        return;
    }

    case DEFINE_PROGRAM_STMT: {
        define_program_stmt_t *stmt = (define_program_stmt_t *)unknown_stmt;
        check_name_not_defined(worker, stmt->name, stmt->head_token);
        program_t *program = compile(worker, stmt->token_list);
        program_spec_t *spec = program_spec_new(stmt->name, program);
        mod_define(worker->mod, (spec_t *) spec);
        return;
    }

    case RUN_PROGRAM_STMT: {
        run_program_stmt_t *stmt = (run_program_stmt_t *)unknown_stmt;
        program_t *program = compile(worker, stmt->token_list);
        size_t base_length = stack_length(worker->return_stack);
        stack_push(worker->return_stack, frame_new(program));
        worker_run_until(worker, base_length);
        worker_interact(worker);
        return;
    }
    }

    assert(false);
}

void
interpret_mod(worker_t *worker) {
    parser_t *parser = parser_new();
    parser->lexer = lexer_new();
    parser->lexer->line_comment_start = "--";
    parser->src = worker->mod->src;
    parser->text = worker->mod->text;
    parser->err = worker->err;
    parser_parse(parser);
    list_t *stmt_list = parser->stmt_list;
    parser_destroy(&parser);

    stmt_t *stmt = list_start(stmt_list);
    while (stmt) {
        interpret_stmt(worker, stmt);
        stmt = list_next(stmt_list);
    }
}
