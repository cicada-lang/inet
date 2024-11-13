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
        assert(stmt);
        return;
    }
    }

    assert(false);
}
