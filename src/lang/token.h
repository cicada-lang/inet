#pragma once

struct token_t {
    char *string;
    size_t start;
    size_t end;
};

token_t *token_new(char *string, size_t start, size_t end);
