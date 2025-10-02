#include <stdio.h>
#include "macros.h"
#include "asserts.h"

int AssertOfMusa(int need_to_call_assert, const char *file, const char *function, int line) {
    if (!need_to_call_assert) {
        printf(FG_BG_ANSI "File: %s, ", file);
        printf(FG_BG_ANSI "Function: %s, ", function);
        printf(FG_BG_ANSI "Line: %d " RESET_ANSI "\n", line);
        printf("\n");
        return 0;
    }
    return 1;
}