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
    file_t *file = fopen(file_name, "r");
    if (!file) {
        fprintf(stderr, "[run] can not open file: %s\n", file_name);
        exit(1);
    }

    mod_t *mod = mod_new(file_name);
    import_builtins(mod);

    worker_t *worker = worker_new(mod);
    worker->debug = debug;

    if (string_ends_with(file_name, ".test.inet")) {
        char *out_file_name = string_append(file_name, ".out");
        file_t *out = fopen(out_file_name, "w");
        if (!out) {
            fprintf(stderr, "[run] can not open out file: %s\n", out_file_name);
            exit(1);
        }

        char *err_file_name = string_append(file_name, ".err");
        file_t *err = fopen(err_file_name, "w");
        if (!err) {
            fprintf(stderr, "[run] can not open err file: %s\n", err_file_name);
            exit(1);
        }

        worker->out = out;
        worker->err = err;
    }

    interpret_text(worker, file_read(file));

    worker_destroy(&worker);
    mod_destroy(&mod);

    fclose(file);
}
