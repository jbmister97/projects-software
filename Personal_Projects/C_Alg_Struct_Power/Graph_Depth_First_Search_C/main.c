#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Graph Depth First Search Method

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

void graph_dfs(graph * g, int u, bool visited[]) {
    if(visited[u]) {return;}
    visited[u] = true;
    printf("%d ",u);
    edge_node * e = g->edges[u];

    while(e != NULL) {
        graph_dfs(g,e->v,visited);
        e = e->next;
    }

    return;
}

int main()
{
    graph * g = create_graph(13,false);
    add_edge(g,0,1,1);
    add_edge(g,1,2,12);
    add_edge(g,1,3,10);
    add_edge(g,2,4,11);
    add_edge(g,2,5,13);
    add_edge(g,3,5,12);
    add_edge(g,3,7,13);
    add_edge(g,4,6,9);
    add_edge(g,5,6,7);
    add_edge(g,6,7,15);
    add_edge(g,8,9,12);
    add_edge(g,8,10,10);
    add_edge(g,9,10,10);
    add_edge(g,10,11,9);
    add_edge(g,11,12,10);
    print_graph(g);

    bool visited[g->nb_nodes];
    for(int i = 0; i < g->nb_nodes; i++) {
        visited[i] = false;
    }

    for(int i = 0; i < g->nb_nodes; i++) {
        graph_dfs(g,i,visited);
    }

    return 0;
}
