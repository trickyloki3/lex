#include "lex.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "trace.c"

int lex_create(struct lex * lex, int node_max, int edge_max, int span_max) {
    lex->node = malloc(node_max * sizeof(*lex->node));
    if(!lex->node)
        goto node_fail;

    lex->node_off = 1;
    lex->node_len = 1;
    lex->node_max = node_max;

    lex->edge = malloc(edge_max * sizeof(*lex->edge));
    if(!lex->edge)
        goto edge_fail;

    lex->edge_off = 1;
    lex->edge_len = 1;
    lex->edge_max = edge_max;

    lex->span = malloc(span_max * sizeof(*lex->span));
    if(!lex->span)
        goto span_fail;

    lex->span_off = 1;
    lex->span_len = 1;
    lex->span_max = span_max;

    return 0;

span_fail:
    free(lex->edge);
edge_fail:
    free(lex->node);
node_fail:
    return 1;
}

void lex_delete(struct lex * lex) {
    free(lex->span);
    free(lex->edge);
    free(lex->node);
}
