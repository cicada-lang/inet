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
        char *file_name = *file_names++;
        if (string_equal(file_name, "--debug")) {
            debug = true;
        }
    }

    file_names = args + 1;
    while (*file_names) {
        char *file_name = *file_names++;
        if (string_ends_with(file_name, ".inet")) {
            run_file(file_name, debug);
        } else {
            fprintf(stderr, "[run] file name must ends with .inet, given file name: %s\n", file_name);
            exit(1);
        }
    }

    return 0;
}

void
run_file(const char *file_name, bool debug) {
    file_t *file = file_open_or_fail(file_name, "r", "[run] can not open file");
    mod_t *mod = mod_new(file_name);
    import_builtins(mod);

    worker_t *worker = worker_new(mod);
    worker->debug = debug;

    if (string_ends_with(file_name, ".test.inet") ||
        string_ends_with(file_name, ".error.inet"))
    {
        worker->out = file_open_or_fail(
            string_append(file_name, ".out"), "w",
            "[run] can not open out file");
    }

    if (string_ends_with(file_name, ".error.inet")) {
        worker->err = file_open_or_fail(
            string_append(file_name, ".err"), "w",
            "[run] can not open err file");
    }

    interpret_text(worker, file_read(file));

    worker_destroy(&worker);
    mod_destroy(&mod);

    fclose(file);
}
