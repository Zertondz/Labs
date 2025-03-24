#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

Table * initialization_table(int size);
int str_chint(unsigned int* n1,int mode);
int check_file(char * fname);
unsigned int search_hash(char *key,Table * table,int *error);
char * readline12(char rasd[]);
unsigned long djb2_hash(char *str,unsigned int msize);
unsigned long polinom_hash(const char* s,unsigned int msize);
unsigned int double_hash(char *str,const unsigned int i,const unsigned msize);
unsigned int near_simp(unsigned int amount);
int NOD(int a,int b);
#endif // TOOLS_H_INCLUDED
