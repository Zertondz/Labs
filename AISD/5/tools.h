#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED
#include "graph.h"
#include <graphviz/gvc.h>
#include <graphviz/cdt.h>
#include <graphviz/pathplan.h>
#include <graphviz/cgraph.h>
Graph *expend_table(Graph* table);
Graph *initialization_table(unsigned int msize);
void delete_all(Graph * graph);
int str_chint(unsigned int* n1,int mode);
Vertex *create_ver(unsigned int x, unsigned int y, int type);
unsigned int search_hash(unsigned int x,unsigned int y,Graph * table,int *error);
unsigned int search_hash_del(unsigned int x,unsigned int y,Graph * table,int *error);
int del_ed_corr(unsigned int x, unsigned int y, Graph * graph);
Edge *create_edge(unsigned int x_to, unsigned int y_to);
int check_coordinates(unsigned int x_f,unsigned int y_f,unsigned int x_to,unsigned int y_to);
int graphvi(Graph *graph);
char *name_node(Vertex *ver);
void serv(Agraph_t *g,Graph *graph);
void recur(Agraph_t *g,Vertex * ver,Agnode_t *n2, Graph *graph);
char * readline12(char rasd[]);
#endif