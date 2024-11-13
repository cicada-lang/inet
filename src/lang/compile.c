#include "index.h"

static void compile_word(const mod_t *mod, program_t *program, const char *word);

program_t *
compile(const mod_t *mod, list_t *token_list) {
    program_t *program = program_new();
    token_t *token = list_start(token_list);
    while (token) {
        compile_word(mod, program, token->string);
        token = list_next(token_list);
    }
    program_build(program);
    return program;
}

void compile_word(const mod_t *mod, program_t *program, const char *word) {
    assert(mod);
    assert(program);
    assert(word);
}
