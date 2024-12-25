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
        assert(a->lineno == 1);
        assert(a->column == 2);

        token_t *b = list_shift(token_list);
        assert(b->lineno == 1);
        assert(b->column == 4);

        token_t *c = list_shift(token_list);
        assert(string_equal(c->string, "c"));
        assert(c->lineno == 2);
        assert(c->column == 3);

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

    {
        lexer->string = "(a)";
        lexer_add_delimiter(lexer, "(");
        lexer_add_delimiter(lexer, ")");

        lexer_run(lexer);
        list_t *token_list = lexer->token_list;
        assert(list_length(token_list) == 3);

        token_t *a = list_shift(token_list);
        assert(string_equal(a->string, "("));

        token_t *b = list_shift(token_list);
        assert(string_equal(b->string, "a"));

        token_t *c = list_shift(token_list);
        assert(string_equal(c->string, ")"));

        list_destroy(&token_list);
        token_destroy(&a);
        token_destroy(&b);
        token_destroy(&c);
    }

    {
        lexer->string = "1 1.0";
        lexer->enable_int = true;
        lexer->enable_float = true;

        lexer_run(lexer);
        list_t *token_list = lexer->token_list;
        assert(list_length(token_list) == 2);

        token_t *a = list_shift(token_list);
        assert(string_equal(a->string, "1"));
        assert(a->kind == INT_TOKEN);
        assert(a->int_value == 1);

        token_t *b = list_shift(token_list);
        assert(string_equal(b->string, "1.0"));
        assert(b->float_value == 1.0);

        list_destroy(&token_list);
        token_destroy(&a);
        token_destroy(&b);
    }

    {
        lexer->string = "\"a\" \"b\" \"\\n\"";
        lexer->enable_string = true;

        lexer_run(lexer);
        list_t *token_list = lexer->token_list;
        assert(list_length(token_list) == 3);

        token_t *a = list_shift(token_list);
        assert(string_equal(a->string, "a"));
        assert(a->kind == STRING_TOKEN);

        token_t *b = list_shift(token_list);
        assert(string_equal(b->string, "b"));
        assert(b->kind == STRING_TOKEN);

        token_t *c = list_shift(token_list);
        assert(string_equal(c->string, "\n"));
        assert(c->kind == STRING_TOKEN);

        list_destroy(&token_list);
        token_destroy(&a);
        token_destroy(&b);
        token_destroy(&c);
    }

    lexer_destroy(&lexer);

    printf("</lexer_test>\n");
}
