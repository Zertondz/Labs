#ifndef ADD_H_INCLUDED
#define ADD_H_INCLUDED
#include "graph.h"
#include <graphviz/gvc.h>
#include <graphviz/cdt.h>
#include <graphviz/pathplan.h>
#include <graphviz/cgraph.h>
void generator();
Agraph_t * graphvi_pr(Graph *graph);
Graph * read_f();
int dial_path_add(Graph *graph);
#endif