#ifndef nfa_h
#define nfa_h

static int node_push(struct lex *, int *);
static int edge_push(struct lex *, int, int);
static int span_push(struct lex *, int, int, int, int);

static void node_cat(struct lex *, int, int);
static void node_sub(struct lex *, int, int);

#endif
