#include "index.h"
#include "../utils/index.h"

static int run(char **args);

void
self_test_command(const command_runner_t *runner) {
    command_t *command = command_create("self-test");
    command->description = "run self test";
    command->run = run;
    command_runner_add_command(runner, command);
}

int
run(char **args) {
    (void) args;

    printf("<self-test>\n");

    test_utils();

    printf("</self-test>\n");
    printf("\n");

    return 0;
}
