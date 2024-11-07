#include "index.h"

static int run_with_runner(char **args, const command_runner_t *runner);

void
default_help_command(const command_runner_t *runner) {
    command_t *command = command_new("help");
    command->description = "print help message";
    command->run_with_runner = run_with_runner;
    command_runner_add_command(runner, command);
}

int
run_with_runner(char **args, const command_runner_t *runner) {
    (void) args;

    command_runner_help(runner);

    return 0;
}
