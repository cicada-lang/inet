#pragma once

command_t *command_new(const char *name);
void command_free(command_t *self);
void command_destroy(command_t **self_pointer);
