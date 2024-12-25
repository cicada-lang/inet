#pragma once

typedef enum {
    GENERIC_TOKEN,
    DELIMITER_TOKEN,
    INT_TOKEN,
    FLOAT_TOKEN,
    STRING_TOKEN,
} token_kind_t;

typedef struct token_t token_t;
typedef struct lexer_t lexer_t;
