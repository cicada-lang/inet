#include "index.h"

static int run(char **args);

void
default_version_command(const command_runner_t *runner) {
    command_t *command = command_create("version");
    command->description = "print version";
    command->run = run;
    command_runner_add_command(runner, command);
}

int
run(char **args) {
    (void) args;

    printf("%s\n", X_VERSION);

    return 0;
}
