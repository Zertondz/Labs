#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef struct Vertex
{
    unsigned int x;
    unsigned int y;
    int type;
    int service;
    struct Edge * edges;
}Vertex;

typedef struct Edge
{
    unsigned int to_x;
    unsigned int to_y;
    struct Edge * next;
}Edge;
typedef struct Graph
{
    unsigned int msize;
    unsigned int csize;
    Vertex ** vertex_table;
}Graph;
int add_ver(Graph ** graph,Vertex *vertex);
int add_edge(Graph * graph,unsigned int from_x,unsigned int from_y,Edge *edge);
int del_ver(unsigned int x,unsigned int y,Graph *graph);
int del_edge(Graph * graph,unsigned int from_x,unsigned int from_y,Edge *edge);
void change_ver(Graph *graph,unsigned int ind,unsigned int x,unsigned int y,unsigned int type);
int *sh_path(Graph *graph, unsigned int x_f, unsigned int y_f, unsigned int x_to, unsigned int y_to, int * error);
void output(Graph * graph);
void travelsal(Graph *graph,unsigned int x, unsigned int y);
void mod_gr(Graph *graph,int * error);
#endif // GRAPH_H_INCLUDED