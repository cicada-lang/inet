#include "index.h"

void
lexer_test(void) {
    printf("<lexer_test>\n");

    {
        list_t *token_list = lex("");
        assert(list_length(token_list) == 0);
    }

    {
        list_t *token_list = lex(" ");
        assert(list_length(token_list) == 0);
    }

    {
        list_t *token_list = lex(" \n \t \n ");
        assert(list_length(token_list) == 0);
    }

    {
        list_t *token_list = lex("a b c");
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
