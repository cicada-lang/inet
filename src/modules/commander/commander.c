#include "index.h"

commander_t *
commander_new(const char *name, const char *version, int argc, char **argv) {
    commander_t *self = new(commander_t);
    self->name = name;
    self->version = version;
    self->argc = argc;
    self->argv = argv;
    self->command_list = list_new_with((destroy_fn_t *) command_destroy);
    return self;
}

void
commander_destroy(commander_t **self_pointer) {
    assert(self_pointer);
    if (*self_pointer) {
        commander_t *self = *self_pointer;
        list_destroy(&self->command_list);
        free(self);
        *self_pointer = NULL;
    }
}


const char *
commander_command_name(const commander_t *self) {
    return self->argv[1];
}

char **
commander_rest_argv(const commander_t *self) {
    return self->argv + 2;
}

size_t
commander_rest_argc(const commander_t *self) {
    return self->argc - 2;
}

void
commander_add(commander_t *self, command_t *command) {
    list_push(self->command_list, command);
}

void
commander_use(commander_t *self, commander_plugin_fn_t *plugin) {
    (*plugin)(self);
}

static const command_t *
commander_default_command(const commander_t *self) {
    command_t *command = list_first(self->command_list);
    while (command) {
        if (string_equal(command->name, "default")) {
            return command;
        }

        command = list_next(self->command_list);
    }

    return NULL;
}

void
commander_help(const commander_t *self) {
    printf("%s %s\n", self->name, self->version);
    printf("\n");

    printf("commands:\n");
    command_t *command = list_first(self->command_list);
    while (command) {
        printf("  %s", command->name);
        if (command->description)
            printf(" -- %s", command->description);
        printf("\n");
        command = list_next(self->command_list);
    }
}

static int
commander_run_command(commander_t *self, const command_t *command) {
    assert(command);
    assert(command->run);
    return (*command->run)(self);
}

int
commander_run(commander_t *self) {
    const char *command_name = commander_command_name(self);

    if (!command_name) {
        const command_t *default_command = commander_default_command(self);
        if (default_command) {
            return commander_run_command(self, default_command);
        } else {
            commander_help(self);
            return 0;
        }
    }

    command_t *command = list_first(self->command_list);
    while (command) {
        if (string_equal(command->name, command_name)) {
            return commander_run_command(self, command);
        }

        command = list_next(self->command_list);
    }

    printf("[commander_run] undefined command: %s\n", command_name);
    return 1;
}
