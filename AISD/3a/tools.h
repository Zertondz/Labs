#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED
#ifdef ITERATOR
Iterator begin(const Table * table);
Iterator end(const Table * table);
Iterator next(const Iterator it);
Iterator id_er();
Iterator next_id(const Iterator it,const unsigned int id);
int ifeq(const Iterator it_a,const Iterator it_b);
Iterator create_it(const Table * table,const int id);
Iterator search_bin_2_0_I(const unsigned int key,const Table * table, int * error);
#else
int search_bin_2_0(const unsigned int key,const Table * table);
#endif
Table * initialization_table(int size);
int str_chint(unsigned int* n1,int mode);
int check_file(char * fname);
char * readline12(char rasd[]);
#endif // TOOLS_H_INCLUDED
