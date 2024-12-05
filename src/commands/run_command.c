#include "index.h"

static int run(commander_t *commander);

void
run_command(commander_t *runner) {
    command_t *command = command_new("run");
    command->description = "run files, use --debug to see each step";
    command->run = run;
    commander_add(runner, command);
}

static void run_file(const char *path, bool debug);

int
run(commander_t *commander) {
    bool debug = false;

    char **paths = commander_rest_argv(commander);
    while (*paths) {
        char *path = *paths++;
        if (string_equal(path, "--debug")) {
            debug = true;
        }
    }

    paths = commander_rest_argv(commander);
    while (*paths) {
        char *path = *paths++;
        if (string_ends_with(path, "--")) continue;
        if (string_ends_with(path, ".inet")) {
            run_file(path, debug);
        } else  {
            fprintf(stderr, "[run] file name must ends with .inet, given file name: %s\n", path);
            exit(1);
        }
    }

    return 0;
}

void
run_file(const char *path, bool debug) {
    file_t *file = file_open_or_fail(path, "r");
    const char *text = file_read_text(file);

    mod_t *mod = mod_new(path, text);
    import_builtins(mod);

    worker_t *worker = worker_new(mod);
    worker->debug = debug;

    interpret_mod(worker);

    fclose(file);
    mod_destroy(&mod);
    worker_destroy(&worker);
}
