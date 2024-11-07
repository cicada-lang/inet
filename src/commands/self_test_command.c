#include "index.h"

static int run(char **args);

void
self_test_command(const command_runner_t *runner) {
    command_t *command = command_new("self-test");
    command->description = "run self test";
    command->run = run;
    command_runner_add_command(runner, command);
}

int
run(char **args) {
    (void) args;

    printf("<self-test>\n");

    list_test();

    printf("</self-test>\n");
    printf("\n");

    return 0;
}
