#include "index.h"

static int run(char **args);

void
run_command(const commander_t *runner) {
    command_t *command = command_new("run");
    command->description = "run files, use --debug to see each step";
    command->run = run;
    commander_add(runner, command);
}

static void run_file(const char *file_name, bool debug);

int
run(char **args) {
    bool debug = false;

    char **file_names = args + 1;
    while (*file_names) {
        char *file_name = *file_names;
        file_names++;
        if (string_equal(file_name, "--debug")) {
            debug = true;
        }
    }

    file_names = args + 1;
    while (*file_names) {
        char *file_name = *file_names;
        file_names++;
        if (!string_starts_with(file_name, "--")) {
            run_file(file_name, debug);
        }
    }

    return 0;
}

void
run_file(const char *file_name, bool debug) {
    file_t *file = fopen(file_name, "r");
    if (!file) {
        fprintf(stderr, "[run] can not open file: %s\n", file_name);
        exit(1);
    }

    char *text = file_read(file);

    mod_t *mod = mod_new(file_name);
    import_builtins(mod);

    worker_t *worker = worker_new(mod);
    worker->debug = debug;

    interpret_text(worker, file_name, text);

    worker_destroy(&worker);
    mod_destroy(&mod);

    fclose(file);
}
