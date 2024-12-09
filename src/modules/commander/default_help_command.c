#include "index.h"

static int run(commander_t *commander);

void
default_help_command(commander_t *commander) {
    command_t *command = command_new("help");
    command->description = "print help message";
    command->run = run;
    commander_add(commander, command);
}

int
run(commander_t *commander) {
    commander_help(commander);

    return 0;
}
