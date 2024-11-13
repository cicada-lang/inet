#include "index.h"

void
interpret(worker_t *worker, stmt_t *unknown_stmt) {
    switch (unknown_stmt->tag) {
    case DEFINE_NODE_STMT: {
        define_node_stmt_t *stmt = (define_node_stmt_t *)unknown_stmt;
        assert(worker);
        assert(stmt);
        return;
    }

    case DEFINE_RULE_STMT: {
        define_rule_stmt_t *stmt = (define_rule_stmt_t *)unknown_stmt;
        assert(stmt);
        return;
    }

    case DEFINE_PROGRAM_STMT: {
        define_program_stmt_t *stmt = (define_program_stmt_t *)unknown_stmt;
        assert(stmt);
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
