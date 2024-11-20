#include "index.h"

static int run_with_commander(char **args, const commander_t *commander);

void
default_version_command(const commander_t *commander) {
    command_t *command = command_new("version");
    command->description = "print version";
    command->run_with_commander = run_with_commander;
    commander_add(commander, command);
}

int
run_with_commander(char **args, const commander_t *commander) {
    (void) args;

    printf("%s\n", commander_version(commander));

    return 0;
}
