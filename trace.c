#include "trace.h"

static int trace_(const char * format, ...) {
    va_list vararg;
    va_start(vararg, format);
    vfprintf(stderr, format, vararg);
    va_end(vararg);
    return 1;
}
