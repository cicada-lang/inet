#pragma once

#define error_report(message) error_report_with_matadata((message), __func__, __FILE__, __LINE__)

void error_report_with_matadata(
    const char *message,
    const char *function_name,
    const char *file_name,
    unsigned int line_number);
