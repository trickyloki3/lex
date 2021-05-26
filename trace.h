#ifndef trace_h
#define trace_h

#define trace(format, ...) trace_("%s (%s:%zu): " format ".\n", __FILE__, __func__, __LINE__, ## __VA_ARGS__)

static int trace_(const char *, ...);

#endif
