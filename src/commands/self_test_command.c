#include "index.h"

static int run(char **args);

void
self_test_command(const commander_t *commander) {
    command_t *command = command_new("self-test");
    command->description = "run self test";
    command->run = run;
    commander_add(commander, command);
}

int
run(char **args) {
    (void) args;

    printf("<self-test>\n");

    string_test();
    list_test();
    stack_test();
    int_test();
    text_test();
    canvas_test();

    worker_test();
    lexer_test();
    parser_test();

    printf("</self-test>\n");

    return 0;
}
