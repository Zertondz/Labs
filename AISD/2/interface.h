#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

typedef struct sinx_degree
{
    int degree;
    double sinx;
}sinx_degree;

typedef struct submissive_node
{
    struct my_queue* input;
    struct my_queue* output;
}submissive_node;

typedef struct top_node
{
    int amount_node,lower_grade, upper_grade;
    float p1,p2,p3;
    struct submissive_node* mass;
    struct sinx_degree* tab;
}top_node;

struct sinx_degree* pop(my_queue* mas);
int push(struct my_queue* mas,sinx_degree* exm);
void delete_all(top_node* mass);
void output_table(const sinx_degree *mass,const int low,const int upper);
void individ_task(const top_node* top);
int probability_check(const float p);
double my_sin(int x);
top_node* create_queue(const int amount_nodes,const int lower_grade,const int upper_grade,const float p1,const float p2,const float p3,const int len_int,const int len_out);
int user_input(int* a, int*b, int *c,float *p1, float *p2, float *p3,int * len_int,int* len_out);
void delete_queue(my_queue * mas);
#endif // INTERFACE_H_INCLUDED
