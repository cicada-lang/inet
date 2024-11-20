#pragma once

typedef void (commander_plugin_t)(const commander_t *commander);

commander_t *commander_new(
    const char *name,
    const char *version,
    int argc,
    char **argv);
void commander_destroy(commander_t **self_pointer);

const char *commander_version(const commander_t *self);
void commander_add(const commander_t *self, command_t *command);
void commander_use(const commander_t *self, commander_plugin_t *plugin);
void commander_help(const commander_t *self);
int commander_run(const commander_t *self);
