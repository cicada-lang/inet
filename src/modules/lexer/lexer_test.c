#include "index.h"

void
lexer_test(void) {
    printf("<lexer_test>\n");

    lexer_t *lexer = lexer_new();

    {
        lexer->string = "";
        lexer_run(lexer);
        assert(list_length(lexer->token_list) == 0);
        list_destroy(&lexer->token_list);
    }

    {
        lexer->string = " ";
        lexer_run(lexer);
        assert(list_length(lexer->token_list) == 0);
        list_destroy(&lexer->token_list);
    }

    {
        lexer->string = " \n \t \n ";
        lexer_run(lexer);
        assert(list_length(lexer->token_list) == 0);
        list_destroy(&lexer->token_list);
    }

    {
        lexer->string = "a b c";
        lexer_run(lexer);
        list_t *token_list = lexer->token_list;
        assert(list_length(token_list) == 3);

        token_t *a = list_shift(token_list);
        assert(string_equal(a->string, "a"));
        token_t *b = list_shift(token_list);
        assert(string_equal(b->string, "b"));
        token_t *c = list_shift(token_list);
        assert(string_equal(c->string, "c"));

        list_destroy(&token_list);
        token_destroy(&a);
        token_destroy(&b);
        token_destroy(&c);
    }

    {
        lexer->line_comment = "//";
        lexer->string = "a b //x\n c";
        lexer_run(lexer);
        list_t *token_list = lexer->token_list;
        assert(list_length(token_list) == 3);

        token_t *a = list_shift(token_list);
        assert(string_equal(a->string, "a"));
        token_t *b = list_shift(token_list);
        assert(string_equal(b->string, "b"));
        token_t *c = list_shift(token_list);
        assert(string_equal(c->string, "c"));

        list_destroy(&token_list);
        token_destroy(&a);
        token_destroy(&b);
        token_destroy(&c);
    }

    {
        lexer->line_comment = "--";
        lexer->string = "a b --x\n c";
        lexer_run(lexer);
        list_t *token_list = lexer->token_list;
        assert(list_length(token_list) == 3);

        token_t *a = list_shift(token_list);
        assert(string_equal(a->string, "a"));
        token_t *b = list_shift(token_list);
        assert(string_equal(b->string, "b"));
        token_t *c = list_shift(token_list);
        assert(string_equal(c->string, "c"));

        list_destroy(&token_list);
        token_destroy(&a);
        token_destroy(&b);
        token_destroy(&c);
    }

    printf("</lexer_test>\n");
}
