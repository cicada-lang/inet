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
        program_t *program = compile(worker->mod, stmt->token_list);
        mod_define_rule(
            worker->mod,
            stmt->first_name,
            stmt->second_name,
            program);
        return;
    }

    case DEFINE_PROGRAM_STMT: {
        define_program_stmt_t *stmt = (define_program_stmt_t *)unknown_stmt;
        program_t *program = compile(worker->mod, stmt->token_list);
        program_spec_t *spec = program_spec_new(stmt->name, program);
        mod_define(worker->mod, (spec_t *) spec);
        return;
    }

    case RUN_PROGRAM_STMT: {
        run_program_stmt_t *stmt = (run_program_stmt_t *)unknown_stmt;
        program_t *program = compile(worker->mod, stmt->token_list);
        stack_push(worker->return_stack, frame_new(program));
        worker_run(worker);
        worker_interact(worker);
        return;
    }
    }

    assert(false);
}

void
interpret_text(worker_t *worker, const char *text) {
    list_t *stmt_list = parse(text);
    stmt_t *stmt = list_start(stmt_list);
    while (stmt) {
        interpret_stmt(worker, stmt);
        stmt = list_next(stmt_list);
    }
}
