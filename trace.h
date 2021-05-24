#ifndef trace_h
#define trace_h

#define trace(format, ...) panic("%s (%s:%zu): " format ".\n", __FILE__, __func__, __LINE__, ## __VA_ARGS__)

static int panic(const char *, ...);

#endif
