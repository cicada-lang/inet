#include "index.h"

void
lexer_test(void) {
    printf("<lexer_test>\n");

    {
        lexer_t *lexer = lexer_new("");
        lexer_lex(lexer);
        list_t *token_list = lexer->token_list;
        assert(list_length(token_list) == 0);
    }

    {
        lexer_t *lexer = lexer_new(" ");
        lexer_lex(lexer);
        list_t *token_list = lexer->token_list;
        assert(list_length(token_list) == 0);
    }

    {
        lexer_t *lexer = lexer_new(" \n \t \n ");
        lexer_lex(lexer);
        list_t *token_list = lexer->token_list;
        assert(list_length(token_list) == 0);
    }

    {
        lexer_t *lexer = lexer_new("a b c");
        lexer_lex(lexer);
        list_t *token_list = lexer->token_list;
        assert(list_length(token_list) == 3);

        token_t *a = list_shift(token_list);
        assert(string_equal(a->string, "a"));
        token_t *b = list_shift(token_list);
        assert(string_equal(b->string, "b"));
        token_t *c = list_shift(token_list);
        assert(string_equal(c->string, "c"));

        token_destroy(&a);
        token_destroy(&b);
        token_destroy(&c);
    }

    printf("</lexer_test>\n");
}
