#ifndef HUEPPH_H_INCLUDED
#define HUEPPH_H_INCLUDED
typedef struct line
{
    int n;
    int *a;
}line;
typedef struct matrix
{
    int lines;
    line * matr;
}matrix;
matrix* create_matrix();
int str_chint(int* n1);
void print_matrix(const matrix* matr);
void delete_matrix(matrix* matr_del);
void delete_matrix_i(matrix* matr_del,int elem);
matrix * idivid_task(matrix* matr);
int round_up(const int a,const int b);
#endif // HUEPPH_H_INCLUDED
