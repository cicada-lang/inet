#pragma once

void interpret_stmt(worker_t *worker, stmt_t *stmt);
void interpret_text(worker_t *worker, const char *src, const char *text);
