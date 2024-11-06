#include "index.h"

struct command_runner_t {
    const char *name;
    const char *version;
    const char *description;
    int argc;
    char **argv;
    list_t *command_list;
};

command_runner_t *
command_runner_create(const char *name, const char *version, int argc, char **argv) {
    command_runner_t *self = allocate(sizeof(command_runner_t));
    self->name = name;
    self->version = version;
    self->argc = argc;
    self->argv = argv;
    self->command_list = list_create();
    return self;
}

void
command_runner_destroy(command_runner_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        command_runner_t *self = *self_pointer;
        list_destroy(&self->command_list, (list_item_free_t *) command_free);
        free(self);
        *self_pointer = NULL;
    }
}

void
command_runner_add_command(const command_runner_t *self, command_t *command) {
    list_push(self->command_list, command);
}

void
command_runner_mount(const command_runner_t *self, command_plugin_t *plugin) {
    (*plugin)(self);
}

static const command_t *
command_runner_default_command(const command_runner_t *self) {
    command_t *command = list_start(self->command_list);
    while (command) {
        if (strcmp(command->name, "default") == 0)
            return command;

        command = list_next(self->command_list);
    }

    return NULL;
}

void
command_runner_help(const command_runner_t *self) {
    printf("%s %s\n", self->name, self->version);
    printf("\n");

    printf("commands:\n");
    command_t *command = list_start(self->command_list);
    while (command) {
        printf("  %s", command->name);
        if (command->description)
            printf(" -- %s", command->description);
        printf("\n");
        command = list_next(self->command_list);
    }
}

static int
command_runner_run_command(const command_runner_t *self, const command_t *command) {
    assert(command);

    char **args = self->argv + 1;
    if (command->run_with_runner)
        return (*command->run_with_runner)(args, self);
    if (command->run)
        return (*command->run)(args);

    printf("no callback function in command: %s\n", command->name);
    return 1;
}

int
command_runner_run(const command_runner_t *self) {
    char *name = self->argv[1];

    if (!name) {
        const command_t *default_command = command_runner_default_command(self);
        if (default_command) {
            return command_runner_run_command(self, default_command);
        } else {
            command_runner_help(self);
            return 0;
        }
    }

    command_t *command = list_start(self->command_list);
    while (command) {
        if (strcmp(command->name, name) == 0)
            return command_runner_run_command(self, command);
        command = list_next(self->command_list);
    }

    printf("command not found: %s\n", name);
    return 1;
}
