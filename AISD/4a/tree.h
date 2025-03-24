#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
typedef struct Node
{
    unsigned int key;
    struct Node *left;
    struct Node *right;
    char * info;
}Node;
typedef struct Tree
{
    Node * root;
}Tree;
int travel_count(Node *root,unsigned int * amount);
int add_elem(Tree* tree, unsigned int key, char * value);
void output_tree_s(Node * root,char * prefix,int is_left);
int travel(Node *root,unsigned int key);
Node ** search(Node *root, unsigned int key,unsigned int * len);
Node ** search_min(Node *root, unsigned int * len);
int del_elem(Tree * tree, unsigned int key);
Tree * read_f_file(int * error);
int graph(Tree * tree);
#endif // TREE_H_INCLUDED