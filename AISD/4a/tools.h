#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED
typedef struct Node_add
{
    unsigned int key;
    struct Node_add *left;
    struct Node_add *right;
    unsigned int amount;
}Node_add;
typedef struct Tree_add
{
    Node_add * root;
}Tree_add;
int str_chint(unsigned int* n1,int mode);
char * readline12(char rasd[]);
void delet_all(Node * root);
void output_ind(Node ** ind,unsigned int len);
char * freadline12(FILE * file);
Tree * generator(unsigned int len,unsigned int ** key);
void test_time();
void write_bin(FILE * file, unsigned int len);
void add_task(FILE * file,Tree_add * tree);
void travel_f(Node_add *root,FILE * file);
void insert_elem(Tree_add *tree,int key);
void delet_all_ad(Node_add * root);
void output_tree_s_a(Node_add * root,char * prefix,int is_left);
#endif // TOOLS_H_INCLUDED