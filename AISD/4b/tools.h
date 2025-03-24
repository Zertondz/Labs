#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED
int str_chint(unsigned int* n1,int mode);
char * readline12(char rasd[]);
void delet_all(Node * root);
void output_ind(Info *ind, unsigned int key);
char * freadline12(FILE * file);
Tree * generator(unsigned int len,unsigned int ** key);
void test_time();
void write_bin(FILE * file, unsigned int len);
Node* balance(Node * node);
Tree * read_f_file_d(Tree * tree,int * error);
char* concat(const char *s1, const char *s2);
#endif // TOOLS_H_INCLUDED