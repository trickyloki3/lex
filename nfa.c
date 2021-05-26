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
        return trace("out of edge");

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
        return trace("out of span");

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

static void node_cat(struct lex * lex, int x, int y) {
    struct node * n;
    struct node * o;

    struct edge * e;
    struct span * s;

    n = lex->node + x;
    o = lex->node + y;

    if(o->edge) {
        e = lex->edge + o->edge;
        while(e->next)
            e = lex->edge + e->next;

        e->next = n->edge;
        n->edge = o->edge;
        o->edge = 0;
    }

    if(o->span) {
        s = lex->span + o->span;
        while(s->next)
            s = lex->span + s->next;

        s->next = n->span;
        n->span = o->span;
        o->span = 0;
    }
}

static void node_sub(struct lex * lex, int x, int y) {
    struct edge * e;
    struct edge * f;

    struct span * s;
    struct span * t;

    e = lex->edge + lex->edge_off;
    f = lex->edge + lex->edge_len;
    while(e < f) {
        if(e->node == x)
            e->node = y;
        e++;
    }

    s = lex->span + lex->span_off;
    t = lex->span + lex->span_len;
    while(s < t) {
        if(s->node == x)
            s->node = y;
        s++;
    }
}
