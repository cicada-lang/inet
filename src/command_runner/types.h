#pragma once

typedef struct _command_runner_t command_runner_t;

typedef void (command_plugin_t)(const command_runner_t *runner);

typedef int (command_run_t)(char **args);
typedef int (command_run_with_runner_t)(char **args, const command_runner_t *runner);

typedef struct {
    const char *name;
    const char *description;
    const char *help;
    command_run_t *run;
    command_run_with_runner_t *run_with_runner;
} command_t;

void default_help_command(const command_runner_t *runner);
void default_version_command(const command_runner_t *runner);
