#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct edge_node
{
    int v;
    int weight;
    struct edge_node * next;
};

typedef struct edge_node edge_node;

struct graph
{
    int nb_nodes;
    int nb_edges;
    // Create array with variable size
    edge_node * * edges;
    bool is_directed;
};

typedef struct graph graph;

graph * create_graph(int nb_nodes, bool is_directed) {
    graph * g = (graph *) malloc(sizeof(graph));
    g->nb_edges = 0;
    g->nb_nodes = nb_nodes;
    g->is_directed = is_directed;
    g->edges = (edge_node * *) malloc(sizeof(edge_node *) * nb_nodes);

    //Initialize all nodes to NULL
    for(int i = 0; i < nb_nodes; i++) {
        g->edges[i] = NULL;
    }
    return g;
}

void print_graph(graph * g) {

    for(int i = 0; i < g->nb_nodes; i++) {
        printf("Vertex %d connected to: ",i);

        edge_node * e = g->edges[i];
        while(e != NULL) {
            printf("%d ", e->v);
            e = e->next;
        }
        printf("\n");
    }
}

void add_edge(graph * g, int u, int v, int weight) {
    edge_node * e = (edge_node *) malloc(sizeof(edge_node));
    e->v = v;
    e->weight = weight;
    e->next = g->edges[u];
    g->edges[u] = e;
    g->nb_edges++;

    // If not directed also add node to edges[v]
    if(!g->is_directed) {
        edge_node * e2 = (edge_node *) malloc(sizeof(edge_node));
        e2->v = u;
        e2->weight = weight;
        e2->next = g->edges[v];
        g->edges[v] = e2;
        g->nb_edges++;
    }
}

int main()
{
    graph * g = create_graph(5,true);
    add_edge(g,1,3,7);
    add_edge(g,1,2,7);
    add_edge(g,2,0,4);
    add_edge(g,2,4,7);
    print_graph(g);
    return 0;
}
