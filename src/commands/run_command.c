#include "index.h"

static int run(char **args);

void
run_command(const commander_t *runner) {
    command_t *command = command_new("run");
    command->description = "run files, use --debug to see each step";
    command->run = run;
    commander_add(runner, command);
}

static void run_file(const char *path, bool debug);

int
run(char **args) {
    bool debug = false;

    char **paths = args + 1;
    while (*paths) {
        char *path = *paths++;
        if (string_equal(path, "--debug")) {
            debug = true;
        }
    }

    paths = args + 1;
    while (*paths) {
        char *path = *paths++;
        if (string_ends_with(path, ".inet")) {
            run_file(path, debug);
        } else {
            fprintf(stderr, "[run] file name must ends with .inet, given file name: %s\n", path);
            exit(1);
        }
    }

    return 0;
}

void
run_file(const char *path, bool debug) {
    file_t *file = file_open_or_fail(path, "r", "[run] can not open file");

    mod_t *mod = mod_new(path);
    import_builtins(mod);

    worker_t *worker = worker_new(mod);
    worker->debug = debug;

    char *out_path = string_append(path, ".out");
    char *err_path = string_append(path, ".err");

    if (string_ends_with(path, ".test.inet"))
        worker->out = file_open_or_fail(out_path, "w", "[run] can not open out path");
    if (string_ends_with(path, ".error.inet"))
        worker->err = file_open_or_fail(err_path, "w", "[run] can not open err path");

    interpret_text(worker, file_read(file));

    if (worker->out && file_size(worker->out) == 0) remove(out_path);
    if (worker->err && file_size(worker->err) == 0) remove(err_path);

    fclose(file);
    fclose(worker->out);
    fclose(worker->err);
    mod_destroy(&mod);
    worker_destroy(&worker);
}
