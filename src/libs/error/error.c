#include "index.h"

void
error_report_with_matadata(
    const char *message,
    const char *function_name,
    const char *file_name,
    unsigned int line_number
) {
    fprintf(
        stderr,
        "%s %s %s %u",
        message,
        function_name,
        file_name,
        line_number);
    assert(false);
}
