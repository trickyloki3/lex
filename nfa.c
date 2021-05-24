#include "nfa.h"

static int node_push(struct lex * lex, int * result) {
    int i;

    struct node * n;

    if(lex->node_len >= lex->node_max)
        return trace("out of node");

    i = lex->node_len;
    n = lex->node + i;
    n->edge = 0;
    n->span = 0;
    n->flag = 0;
    *result = i;

    lex->node_len++;

    return 0;
}

static int edge_push(struct lex * lex, int x, int y) {
    int i;

    struct edge * e;
    struct node * n;

    if(lex->edge_len >= lex->edge_max)
        return panic("out of edge");

    i = lex->edge_len;
    e = lex->edge + i;
    n = lex->node + x;
    e->node = y;
    e->next = n->edge;
    n->edge = i;

    lex->edge_len++;

    return 0;
}

static int span_push(struct lex * lex, int a, int b, int x, int y) {
    int i;

    struct span * s;
    struct node * n;

    if(lex->span_len >= lex->span_max)
        return panic("out of span");

    i = lex->span_len;
    s = lex->span + i;
    n = lex->node + x;
    s->a = a;
    s->b = b;
    s->node = y;
    s->next = n->span;
    n->span = i;

    lex->span_len++;

    return 0;
}
