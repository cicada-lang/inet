#include "index.h"

static int run(char **args);

void
run_command(const commander_t *runner) {
    command_t *command = command_new("run");
    command->description = "run files, use --debug to see each step";
    command->run = run;
    commander_add_command(runner, command);
}

static int run_file(const char *file_name, bool debug);

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
            int status = run_file(file_name, debug);
            if (status != 0) return status;
        }
    }

    return 0;
}

int
run_file(const char *file_name, bool debug) {
    if (!file_name) {
        printf("[run] I expect a file name.\n");
        return 1;
    }

    FILE *file = fopen(file_name, "r");
    if (!file) {
        printf("[run] I file to open file: %s\n", file_name);
        return 1;
    }

    char *text = file_read(file);

    mod_t *mod = mod_new();
    import_builtins(mod);

    worker_t *worker = worker_new(mod);
    worker->debug = debug;
    interpret_text(worker, file_name, text);

    worker_destroy(&worker);
    mod_destroy(&mod);

    fclose(file);
    return 0;
}
