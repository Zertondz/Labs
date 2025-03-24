typedef struct NODE
{
    struct sinx_degree* data;
    struct NODE* next;
}NODE;

typedef struct my_queue
{
    struct NODE* head;
    struct NODE* tail;
    int amount;
}my_queue;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "interface.h"

top_node* create_queue(const int amount_nodes,const int lower_grade,const int upper_grade,const float p1,const float p2,const float p3,const int len_int,const int len_out)
{
    top_node* top = (top_node*)malloc(sizeof(top_node));
    top->p1 = p1,top->p2 = p2,top->p3 = p3,top->lower_grade = lower_grade,top->upper_grade = upper_grade;
    top->amount_node = amount_nodes, top->mass = (submissive_node*)malloc(sizeof(submissive_node)*amount_nodes);
    top->tab = (sinx_degree*)malloc(sizeof(sinx_degree)*(upper_grade - lower_grade + 1));
    for (int i = 0;i < amount_nodes;i++)
    {
        ((top->mass)[i]).input = (my_queue*)calloc(1,sizeof(my_queue)), ((top->mass)[i]).output = (my_queue*)calloc(1,sizeof(my_queue));
    }
    return top;
}

int push(my_queue* mas,sinx_degree* exm)
{
    NODE * node = (NODE*)calloc(1,sizeof(NODE));
    node->data = exm;
    if (0 != mas->amount)
    {
        mas->tail->next = node;
        mas->tail = node;
        mas->amount++;
    }
    else
    {
        mas->head = node;
        mas->tail = node;
        mas->amount++;
    }
    return 0;
}

void delete_queue(my_queue * mas)
{
    free(mas);
}

sinx_degree* pop(my_queue* mas)
{
    sinx_degree* data = NULL;
    if (0 != mas->amount)
    {
        data = mas->head->data;
        if(mas->amount == 1) {free(mas->head);mas->head = NULL; mas->tail = NULL;}
        else
        {
            NODE *mem = mas->head;
            mas->head = mas->head->next;
            free(mem);
        }
        mas->amount--;
    }
    else return NULL;
    return data;
}
