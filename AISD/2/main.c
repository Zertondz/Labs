typedef struct my_queue my_queue;
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
    srand(time(NULL));
    int amount_nodes = 0, lower_grade = 0, upper_grade = 0,flag_input = 0,len_out = 0,len_int = 0;
    top_node* origin = NULL;
    float p1 = 0.0, p2 = 0.0, p3 = 0.0;
    while(1)
    {
        flag_input = user_input(&amount_nodes, &lower_grade, &upper_grade, &p1, &p2, &p3,&len_int,&len_out);
        if (flag_input == -1){printf("The input is completed\n"); return -1;}
        else if(flag_input == -2){printf("Input error\n"); continue;}
        origin = create_queue(amount_nodes, lower_grade, upper_grade, p1, p2, p3, len_int, len_out);
        individ_task(origin);
        delete_all(origin);
        origin = NULL;
    }
    return 0;
}

void individ_task(const top_node* top)
{
    int grade = top->lower_grade,j = 0,d = 0;
    sinx_degree* package = NULL;
    while(1)
    {
        for(int i = 0;i < top->amount_node;i++)
        {
            if(grade != (top->upper_grade + 1))
            {
                if(probability_check(top->p1))
                {
                    package = (sinx_degree*)calloc(1, sizeof(sinx_degree));
                    package->degree = grade;
                    d = push((top->mass[i]).input,package);
                    if (d != -1)grade++;
                    else free(package);
                }
                package = NULL;
            }
            if(probability_check(top->p2))
            {
                package = pop((top->mass[i]).input);
                if (package != NULL)
                {
                    package->sinx = my_sin(package->degree);
                    d = push((top->mass[i]).output,package);
                    if (d == -1)push((top->mass[i]).input,package);
                    package = NULL;
                }
            }
            if(probability_check(top->p3))
            {
                package = pop((top->mass[i]).output);
                if (package != NULL)
                {
                    (top->tab)[j].degree = package->degree;
                    (top->tab)[j].sinx = package->sinx;
                    j++;
                    free(package);
                }
                package = NULL;
            }
            if(j == (top->upper_grade - top->lower_grade + 1))break;
        }
        if(j == (top->upper_grade - top->lower_grade + 1))break;
    }
    output_table(top->tab,top->lower_grade,top->upper_grade);
}

void output_table(const sinx_degree*mass,const int low,const int upper)
{
    printf("|| grade |  sin(x)  ||\n");
    for(int i = low;i <=upper;i++)
    {
        int j = 0;
        while(1)
        {
            if (mass[j].degree == i)
            {
                printf("||%6d | %1.7lf||\n",i,mass[j].sinx);
                break;
            }
            j++;
        }
    }
}

int probability_check(const float p)
{
    const float RAND_MAX_F = RAND_MAX;
    float p0 = rand()/RAND_MAX_F;
    if(p0 > p) return 0;
    else if (p0 <= p) return 1;
    return -1;
}

double my_sin(int x)
{
    double itog = 0.0,mult = 0, x_d = 0;
    while(x < 0)x+=360;

    x_d = (x % 360)*(M_PI/180.0);
    mult = x_d;
    for (int i = 0;i < 12;i++)
    {
        itog += mult;
        mult = (mult*x_d*x_d*(-1))/((2 + i * 2)*(2 + i * 2 + 1));
    }
    return itog;
}

void delete_all(top_node* mass)
{
    int k = mass->amount_node;
    for (int i = 0;i < k;i++)
    {
        submissive_node dop_mass = (mass->mass)[i];
        delete_queue(dop_mass.input);
        delete_queue(dop_mass.output);
    }
    free(mass->tab);
    free(mass->mass);
    free(mass);
}
int user_input(int* a, int*b, int *c,float *p1, float *p2, float *p3,int * len_int,int* len_out)
{
    #ifdef VECTOR
    printf("Enter the length of the two queues to output and input: \n");
    int d = scanf("%d %d",len_out, len_int);
    if((d == -1))return -1;
    else if(d != 2)return -2;
    if((*len_int) <= 0)return -2;
    if((*len_out) <= 0)return -2;
    #elif LIST
    int d = 0;
    #endif // LIST
    printf("Enter the number of nodes, the range of angles(two integers), 3 probabilities(p1,p2,p3): \n");
    d = scanf("%d %d %d %f %f %f",a, b, c, p1, p2, p3);
    if((*c) < (*b))return -2;
    if(((*p1) > 1)||((*p1) < 0))return -2;
    if(((*p2) > 1)||((*p2) < 0))return -2;
    if(((*p3) > 1)||((*p3) < 0))return -2;
    if((d == -1))return -1;
    else if(d != 6)return -2;
    return 0;
}
