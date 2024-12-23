#include "index.h"

void
char_test(void) {
    printf("<char_test>\n");

    assert(char_to_hex('0') == 0);
    assert(char_to_hex('1') == 1);
    assert(char_to_hex('2') == 2);
    assert(char_to_hex('3') == 3);
    assert(char_to_hex('4') == 4);
    assert(char_to_hex('5') == 5);
    assert(char_to_hex('6') == 6);
    assert(char_to_hex('7') == 7);
    assert(char_to_hex('8') == 8);
    assert(char_to_hex('9') == 9);

    assert(char_to_hex('a') == 0xa);
    assert(char_to_hex('b') == 0xb);
    assert(char_to_hex('c') == 0xc);
    assert(char_to_hex('d') == 0xd);
    assert(char_to_hex('e') == 0xe);
    assert(char_to_hex('f') == 0xf);

    assert(char_to_hex('A') == 0xA);
    assert(char_to_hex('B') == 0xB);
    assert(char_to_hex('C') == 0xC);
    assert(char_to_hex('D') == 0xD);
    assert(char_to_hex('E') == 0xE);
    assert(char_to_hex('F') == 0xF);

    assert(char_is_digit('0'));
    assert(char_is_digit('1'));
    assert(char_is_digit('2'));
    assert(char_is_digit('3'));
    assert(char_is_digit('4'));
    assert(char_is_digit('5'));
    assert(char_is_digit('6'));
    assert(char_is_digit('7'));
    assert(char_is_digit('8'));
    assert(char_is_digit('9'));

    assert(!char_is_digit('a'));
    assert(!char_is_digit('A'));

    printf("</char_test>\n");
}
