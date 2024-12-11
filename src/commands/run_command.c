#include "index.h"

static int run(commander_t *commander);

void
run_command(commander_t *runner) {
    command_t *command = command_new("run");
    command->description = "run files";
    command->run = run;
    commander_add(runner, command);
}

void
run_file(const char *path, size_t log_level) {
    file_t *file = file_open_or_fail(path, "r");
    const char *string = file_read_string(file);
    fclose(file);

    mod_t *mod = mod_new(path, string);
    import_builtins(mod);

    worker_t *worker = worker_new(mod);
    worker->log_level = log_level;

    interpret_mod(worker);

    mod_destroy(&mod);
    worker_destroy(&worker);
}

int
run(commander_t *commander) {
    size_t log_level = false;

    char **paths = commander_rest_argv(commander);
    while (*paths) {
        char *path = *paths++;
        if (string_equal(path, "--log-level=1")) {
            log_level = 1;
        }
    }

    paths = commander_rest_argv(commander);
    while (*paths) {
        char *path = *paths++;
        if (string_starts_with(path, "--")) 
            continue;

        if (string_ends_with(path, ".inet")) {
            run_file(path, log_level);
        } else  {
            fprintf(stderr, "[run] file name must ends with .inet, given file name: %s\n", path);
            exit(1);
        }
    }

    return 0;
}
