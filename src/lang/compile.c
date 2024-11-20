#include "index.h"

static void compile_token(
    const worker_t *worker,
    program_t *program,
    const token_t *token);

program_t *
compile(const worker_t *worker, list_t *token_list) {
    program_t *program = program_new();
    token_t *token = list_start(token_list);
    while (token) {
        compile_token(worker, program, token);
        token = list_next(token_list);
    }

    program_build(program);
    return program;
}

static bool is_free_wire_ref(const char *word);
static bool is_reversed_free_wire_ref(const char *word);

static char *parse_free_wire_ref_node_name(const char *word);
static char *parse_free_wire_ref_port_name(const char *word);

static char *parse_reversed_free_wire_ref_node_name(const char *word);
static char *parse_reversed_free_wire_ref_port_name(const char *word);

void
compile_token(const worker_t *worker, program_t *program, const token_t *token) {
    mod_t *mod = worker->mod;
    char *word = token->string;

    if (is_free_wire_ref(word)) {
        char *node_name = parse_free_wire_ref_node_name(word);
        char *port_name = parse_free_wire_ref_port_name(word);
        check_node_name_defined(worker, node_name, token);
        check_port_name_defined(worker, node_name, port_name, token);
        emit_use_free_wire(mod, program, node_name, port_name);
    } else if (is_reversed_free_wire_ref(word)) {
        char *node_name = parse_reversed_free_wire_ref_node_name(word);
        char *port_name = parse_reversed_free_wire_ref_port_name(word);
        check_node_name_defined(worker, node_name, token);
        check_port_name_defined(worker, node_name, port_name, token);
        emit_reconnect_free_wire(mod, program, node_name, port_name);
    } else {
        check_name_defined(worker, word, token);
        emit_call(mod, program, word);
    }
}

bool is_free_wire_ref(const char *word) {
    return string_starts_with(word, "(") && !string_ends_with(word, ")");
}

bool is_reversed_free_wire_ref(const char *word) {
    return !string_starts_with(word, "(") && string_ends_with(word, ")");
}

char *parse_free_wire_ref_node_name(const char *word) {
    assert(string_starts_with(word, "("));
    int i = string_find_index(word, ')');
    assert(i != -1);
    return string_slice(word, 1, i);
}

char *parse_free_wire_ref_port_name(const char *word) {
    assert(string_starts_with(word, "("));
    int i = string_find_index(word, ')');
    assert(i != -1);
    return string_slice(word, i + 2, strlen(word));
}

char *parse_reversed_free_wire_ref_node_name(const char *word) {
    int s = string_find_index(word, '(');
    assert(s != -1);
    int e = string_find_index(word, ')');
    assert(e != -1);
    return string_slice(word, s + 1, e);
}

char *parse_reversed_free_wire_ref_port_name(const char *word) {
    int s = string_find_index(word, '(');
    assert(s != -1);
    assert(word[s - 1] == '-');
    return string_slice(word, 0, s - 1);
}
