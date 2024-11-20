#pragma once

typedef struct command_t command_t;
typedef struct commander_t commander_t;

void default_help_command(const commander_t *commander);
void default_version_command(const commander_t *commander);
