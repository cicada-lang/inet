#include "deps.h"
#include "commands/index.h"
#include "lang/index.h"
#include "version.h"

int
main(int argc, char *argv[]) {
    command_runner_t *runner = command_runner_new(
        "inet", INET_VERSION, argc, argv);

    command_runner_mount(runner, self_test_command);
    command_runner_mount(runner, default_help_command);
    command_runner_mount(runner, default_version_command);

    int status_code = command_runner_run(runner);
    command_runner_destroy(&runner);
    return status_code;
}
