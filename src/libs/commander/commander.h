#pragma once

typedef void (command_plugin_t)(const commander_t *commander);

typedef int (command_run_t)(char **args);
typedef int (command_run_with_commander_t)(char **args, const commander_t *commander);

typedef struct {
    const char *name;
    const char *description;
    const char *help;
    command_run_t *run;
    command_run_with_commander_t *run_with_commander;
} command_t;

commander_t *commander_new(const char *name, const char *version, int argc, char **argv);
void commander_destroy(commander_t **self_pointer);

const char *commander_version(const commander_t *self);
void commander_add_command(const commander_t *self, command_t *command);
void commander_mount(const commander_t *self, command_plugin_t *plugin);
void commander_help(const commander_t *self);
int commander_run(const commander_t *self);
