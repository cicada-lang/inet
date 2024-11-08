#pragma once

typedef struct commander_t commander_t;

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

void default_help_command(const commander_t *commander);
void default_version_command(const commander_t *commander);
