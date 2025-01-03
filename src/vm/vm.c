#include "index.h"

static list_t *
lex_code(const char *code) {
    lexer_t *lexer = lexer_new();
    lexer->enable_int = true;
    lexer->enable_float = true;
    lexer->enable_string = true;
    lexer->line_comment = "//";
    lexer->string = code;
    lexer_run(lexer);

    list_t *token_list = lexer->token_list;
    lexer_destroy(&lexer);
    return token_list;
}

vm_t *
vm_new(mod_t *mod) {
    vm_t *self = new(vm_t);
    self->mod = mod;
    self->token_list = lex_code(mod->code);
    self->active_wire_list = list_new();
    // TODO We should use value_destroy to create value_stack.
    self->value_stack = stack_new();
    self->return_stack = stack_new_with((destroy_fn_t *) frame_destroy);
    self->wire_set = set_new();
    self->node_set = set_new();
    self->node_id_count = 0;
    self->log_level = 0;
    return self;
}

void
vm_destroy(vm_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        vm_t *self = *self_pointer;
        list_destroy(&self->token_list);
        list_destroy(&self->active_wire_list);
        stack_destroy(&self->value_stack);
        stack_destroy(&self->return_stack);
        set_destroy(&self->wire_set);
        set_destroy(&self->node_set);
        free(self);
        *self_pointer = NULL;
    }
}

void
vm_print(const vm_t *self, file_t *file) {
    fprintf(file, "<vm>\n");

    size_t active_wire_list_length = list_length(self->active_wire_list);
    fprintf(file, "<active-wire-list length=\"%lu\">\n", active_wire_list_length);
    wire_t *active_wire = list_first(self->active_wire_list);
    while (active_wire) {
        wire_print(active_wire, file);
        fprintf(file, "\n");
        active_wire = list_next(self->active_wire_list);
    }
    fprintf(file, "</active-wire-list>\n");

    vm_print_return_stack(self, file);
    vm_print_value_stack(self, file);

    fprintf(file, "</vm>\n");
}

void
vm_print_return_stack(const vm_t *self, file_t *file) {
    size_t return_stack_length = stack_length(self->return_stack);
    fprintf(file, "<return-stack length=\"%lu\">\n", return_stack_length);
    for (size_t i = 0; i < return_stack_length; i++) {
        frame_t *frame = stack_get(self->return_stack, i);
        frame_print(frame, file);
    }

    fprintf(file, "</return-stack>\n");
}

void
vm_print_value_stack(const vm_t *self, file_t *file) {
    size_t value_stack_length = stack_length(self->value_stack);
    fprintf(file, "<value-stack length=\"%lu\">\n", value_stack_length);
    for (size_t i = 0; i < value_stack_length; i++) {
        value_t value = stack_get(self->value_stack, i);
        value_print(value, file);
        fprintf(file, "\n");
    }

    fprintf(file, "</value-stack>\n");
}

void
vm_connect_top_wire_pair(vm_t *self) {
    wire_t *second_wire = stack_pop(self->value_stack);
    wire_t *first_wire = stack_pop(self->value_stack);

    wire_t *first_opposite = vm_wire_connect(self, second_wire, first_wire);

    vm_maybe_add_active_wire(
        self,
        first_opposite,
        first_opposite->opposite);
}

void
vm_maybe_add_active_wire(
    vm_t *self,
    wire_t *first_wire,
    wire_t *second_wire
) {
    if (wire_is_principal(first_wire) && wire_is_principal(second_wire)) {
        assert(first_wire->opposite == second_wire);
        assert(second_wire->opposite == first_wire);

        list_push(self->active_wire_list, first_wire);
    }
}


node_t *
vm_add_node(vm_t* self, const node_def_t *def) {
    node_t *node = node_new(def, ++self->node_id_count);
    set_add(self->node_set, node);
    return node;
}

void
vm_delete_node(vm_t* self, node_t *node) {
    set_delete(self->node_set, node);
    node_destroy(&node);
}

wire_t *
vm_add_wire(vm_t* self) {
    wire_t *wire = wire_new();
    set_add(self->wire_set, wire);
    return wire;
}

void
vm_delete_wire(vm_t* self, wire_t *wire) {
    set_delete(self->wire_set, wire);
    wire_destroy(&wire);
}

wire_t *
vm_wire_connect(vm_t* self, wire_t *first_wire, wire_t *second_wire) {
    wire_t *first_opposite = first_wire->opposite;
    wire_t *second_opposite = second_wire->opposite;

    first_opposite->opposite = second_opposite;
    second_opposite->opposite = first_opposite;

    vm_delete_wire(self, first_wire);
    vm_delete_wire(self, second_wire);

    return first_opposite;
}
