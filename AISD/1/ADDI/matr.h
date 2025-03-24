#ifndef MATR_H_INCLUDED
#define MATR_H_INCLUDED
typedef struct line
{
    int n;
    int offset;
}line;
typedef struct matrix
{
    int lines;
    char * name_f;
    line * matr;
}matrix;
char* create_keyboard_matrix(int *d);
int str_chint(int* n1);
char * readline12(char rasd[]);
matrix* read_matr(char * name);
matrix* idivid_task(matrix* individ_matr);
int round_up(const int a,const int b);
void print_matrix(const matrix* matr);
void delete_all(matrix* matr_del);
#endif // MATR_H_INCLUDED
