#pragma once

typedef void (commander_plugin_fn_t)(commander_t *commander);

struct commander_t {
    const char *name;
    const char *version;
    const char *description;
    int argc;
    char **argv;
    list_t *command_list;
};

commander_t *commander_new(
    const char *name,
    const char *version,
    int argc,
    char **argv);
void commander_destroy(commander_t **self_pointer);

const char *commander_command_name(const commander_t *self);
char **commander_rest_argv(const commander_t *self);
size_t commander_rest_argc(const commander_t *self);

void commander_add(commander_t *self, command_t *command);
void commander_use(commander_t *self, commander_plugin_fn_t *plugin);
void commander_help(const commander_t *self);
int commander_run(commander_t *self);
