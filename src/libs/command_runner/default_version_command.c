#include "index.h"

static int run_with_runner(char **args, const command_runner_t *runner);

void
default_version_command(const command_runner_t *runner) {
    command_t *command = command_new("version");
    command->description = "print version";
    command->run_with_runner = run_with_runner;
    command_runner_add_command(runner, command);
}

int
run_with_runner(char **args, const command_runner_t *runner) {
    (void) args;

    printf("%s\n", command_runner_version(runner));

    return 0;
}
