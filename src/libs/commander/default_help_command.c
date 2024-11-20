#include "index.h"

static int run_with_commander(char **args, const commander_t *commander);

void
default_help_command(const commander_t *commander) {
    command_t *command = command_new("help");
    command->description = "print help message";
    command->run_with_commander = run_with_commander;
    commander_add(commander, command);
}

int
run_with_commander(char **args, const commander_t *commander) {
    (void) args;

    commander_help(commander);

    return 0;
}
