#include "deps.h"
#include "config.h"
#include "commands/index.h"

int
main(int argc, char *argv[]) {
    commander_t *commander = commander_new("inet", INET_VERSION, argc, argv);

    commander_mount(commander, self_test_command);
    commander_mount(commander, default_help_command);
    commander_mount(commander, default_version_command);

    int status = commander_run(commander);
    commander_destroy(&commander);
    return status;
}
