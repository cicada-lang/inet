#include "index.h"

void
execute_all(vm_t *vm) {
    while (!list_is_empty(vm->token_list)) {
        execute_one(vm);
    }
}
