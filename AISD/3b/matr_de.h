#ifndef MATR_DE_H_INCLUDED
#define MATR_DE_H_INCLUDED
typedef struct Table
{
    struct KeySpace *ks;
    unsigned int msize;
    unsigned int csize;
}Table;

typedef struct KeySpace
{
    int busy;
    char * key;
    struct Node *node;
}KeySpace;

typedef struct Node
{
    unsigned int release;
    char *info;
    struct Node* next;
}Node;

int input_in_table(char* key,char * value_in, Table ** table);
void output_table(const Table* table);
void delete_all(Table* table);
int delete_key_elem(char * key, Table* table);
int delete_key_elem_rel(char * key,const unsigned int release, Table* table);
Table* search_key_elem(char * key, Table * table);
Table* search_key_elem_rel(char * key,const unsigned int release, Table * table);
void output_table_files(char *fname,const Table* table);
Table* input_from_file(char * fname);
Table *  expend_table(Table * table);
#endif // MATR_DE_H_INCLUDED
