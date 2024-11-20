#pragma once

typedef int (command_run_t)(char **args);
typedef int (command_run_with_commander_t)(char **args, const commander_t *commander);

struct command_t {
    const char *name;
    const char *description;
    const char *help;
    command_run_t *run;
    command_run_with_commander_t *run_with_commander;
};

command_t *command_new(const char *name);
void command_destroy(command_t **self_pointer);
