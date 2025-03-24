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
    unsigned int key;
    struct Node *node;
}KeySpace;

typedef struct Node
{
    unsigned int release;
    unsigned int *info;
    struct Node* next;
}Node;
#ifdef ITERATOR
typedef struct Iterator
{
    struct KeySpace * ptr;
}Iterator;
Iterator input_in_table(const unsigned int key,const unsigned value_in, Table * table);
Iterator delete_key_elem(const Iterator ind, Table* table);
Iterator delete_key_elem_rel(const Iterator ind,const unsigned int release, Table* table);
void output_table_i(const Iterator ind);
#else
int input_in_table(const unsigned int key,const unsigned value_in, Table * table);
int delete_key_elem(const unsigned int key, Table* table);
int delete_key_elem_rel(const unsigned int key,const unsigned int release, Table* table);
Table* search_key_elem(const unsigned int key,const Table * table);
#endif
void output_table(const Table* table);
void delete_all(Table* table);
Table* search_key_elem_rel(const unsigned int key,const unsigned int release, const Table * table);
void output_table_files(char *fname,const Table* table);
Table* input_from_file(char * fname);
#endif // MATR_DE_H_INCLUDED
