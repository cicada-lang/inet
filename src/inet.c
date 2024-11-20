#include "deps.h"
#include "config.h"
#include "commands/index.h"

static void setup_io(void);

int
main(int argc, char *argv[]) {
    setup_io();

    commander_t *commander = commander_new("inet", INET_VERSION, argc, argv);

    commander_use(commander, run_command);
    commander_use(commander, default_help_command);
    commander_use(commander, default_version_command);
    commander_use(commander, self_test_command);

    int status = commander_run(commander);
    commander_destroy(&commander);
    return status;
}

void
setup_io(void) {
    setbuf(stdout, NULL);
}
