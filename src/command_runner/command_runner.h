#pragma once

command_runner_t *command_runner_new(const char *name, const char *version, int argc, char **argv);
void command_runner_destroy(command_runner_t **self_pointer);

void command_runner_add_command(const command_runner_t *self, command_t *command);
void command_runner_mount(const command_runner_t *self, command_plugin_t *plugin);
void command_runner_help(const command_runner_t *self);
int command_runner_run(const command_runner_t *self);
