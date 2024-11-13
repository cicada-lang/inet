#include "index.h"

program_t *
compile(const mod_t *mod, list_t *token_list) {
    program_t *program = program_new();
    token_t *token = list_start(token_list);
    while (token) {
        emit_word(mod, program, token->string);
        token = list_next(token_list);
    }
    program_build(program);
    return program;
}
