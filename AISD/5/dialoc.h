#ifndef DIALOC_H_INCLUDED
#define DIALOC_H_INCLUDED
#include "graph.h"
int dia_add_ver(Graph **graph);
int dia_add_edge(Graph *graph);
int dia_del_ver(Graph *graph);
int dia_del_edge(Graph *graph);
int dia_change_ver(Graph *graph);
int dia_traverlas(Graph *graph);
int dial_path(Graph *graph);
int dia_mod(Graph *graph);
#endif // DIALOC_H_INCLUDED