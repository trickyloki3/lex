#include "lex.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "trace.c"
#include "nfa.c"

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

void lex_print(struct lex * lex) {
    int i;

    struct node * n;
    struct edge * e;
    struct span * s;

    if(lex->node_len > 1)
        printf("[node] (%d, %d, %d)\n", lex->node_off, lex->node_len, lex->node_max);

    for(i = 1; i < lex->node_len; i++) {
        n = lex->node + i;
        printf("%d: (%d, %d, %d)\n", i, n->edge, n->span, n->flag);
    }

    if(lex->edge_len > 1)
        printf("[edge] (%d, %d, %d)\n", lex->edge_off, lex->edge_len, lex->edge_max);

    for(i = 1; i < lex->edge_len; i++) {
        e = lex->edge + i;
        printf("%d: (%d, %d)\n", i, e->node, e->next);
    }

    if(lex->span_len > 1)
        printf("[span] (%d, %d, %d)\n", lex->span_off, lex->span_len, lex->span_max);

    for(i = 1; i < lex->span_len; i++) {
        s = lex->span + i;
        printf("%d: (%d, %d, %d, %d)\n", i, s->a, s->b, s->node, s->next);
    }
}
