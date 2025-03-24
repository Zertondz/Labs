typedef struct my_queue
{
    int len;
    int head;
    int teil;
    int amount;
    struct sinx_degree* work_q;
}my_queue;
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
top_node* create_queue(const int amount_nodes,const int lower_grade,const int upper_grade,const float p1,const float p2,const float p3,const int len_int,const int len_out)
{
    top_node* top = (top_node*)malloc(sizeof(top_node));
    top->p1 = p1,top->p2 = p2,top->p3 = p3,top->lower_grade = lower_grade,top->upper_grade = upper_grade;
    top->amount_node = amount_nodes, top->mass = (submissive_node*)malloc(sizeof(submissive_node)*amount_nodes);
    top->tab = (sinx_degree*)malloc(sizeof(sinx_degree)*(upper_grade - lower_grade + 1));
    for (int i = 0;i < amount_nodes;i++)
    {
        ((top->mass)[i]).input = (my_queue*)calloc(1,sizeof(my_queue)), ((top->mass)[i]).output = (my_queue*)calloc(1,sizeof(my_queue));
        (((top->mass)[i]).input)->len = len_int,(((top->mass)[i]).output)->len = len_out;
        (((top->mass)[i]).input)->work_q = (sinx_degree*)calloc(len_int, sizeof(sinx_degree));
        (((top->mass)[i]).output)->work_q = (sinx_degree*)calloc(len_out, sizeof(sinx_degree));
    }
    return top;
}

int push(my_queue* mas, sinx_degree* exm)
{
    if (mas->len != mas->amount)
    {
        (mas->work_q)[mas->teil].degree = exm->degree;
        (mas->work_q)[mas->teil].sinx = exm->sinx;
        mas->teil = (mas->teil + 1) % mas->len;
        mas->amount++;
    }
    else return -1;
    free(exm);
    return 0;
}

void delete_queue(my_queue * mas)
{
    free(mas->work_q);
    free(mas);
}

sinx_degree* pop(my_queue* mas)
{
    sinx_degree* data = NULL;
    if (0 != mas->amount)
    {
        data = (sinx_degree*)malloc(sizeof(sinx_degree));
        data->degree = (mas->work_q)[mas->head].degree;
        data->sinx = (mas->work_q)[mas->head].sinx;
        mas->head = (mas->head + 1) % mas->len;
        mas->amount--;
    }
    else return NULL;
    return data;
}

