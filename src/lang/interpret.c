#include "index.h"

void
interpret(worker_t *worker, stmt_t *unknown_stmt) {
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
            char *word = input_token->string;
            if (string_ends_with(word, "!"))
                word = string_slice(word, 0, strlen(word) - 1);
            spec->port_specs[index] = port_spec_new(word, false);
            input_token = list_next(stmt->input_token_list);
            index++;
        }

        token_t *output_token = list_start(stmt->output_token_list);
        while (output_token) {
            char *word = output_token->string;
            if (string_ends_with(word, "!"))
                word = string_slice(word, 0, strlen(word) - 1);
            spec->port_specs[index] = port_spec_new(word, false);
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
