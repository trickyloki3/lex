#ifndef lex_h
#define lex_h

struct node {
    int edge;
    int span;
    int flag;
};

struct edge {
    int node;
    int next;
};

struct span {
    int a;
    int b;
    int node;
    int next;
};

struct lex {
    struct node * node;
    int node_off;
    int node_len;
    int node_max;
    struct edge * edge;
    int edge_off;
    int edge_len;
    int edge_max;
    struct span * span;
    int span_off;
    int span_len;
    int span_max;
};

int lex_create(struct lex *, int, int, int);
void lex_delete(struct lex *);

#endif
