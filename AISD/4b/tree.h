#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
typedef struct Node
{
    unsigned int key;
    struct Node *left;
    struct Node *right;
    unsigned int height;
    struct Info * info;
}Node;
typedef struct Info
{
    char * value;
    struct Info * next;
}Info;
typedef struct Tree
{
    Node * root;
}Tree;
Node * create_elem(unsigned int key,char * value);
int travel_min_elem(Node *root,unsigned int * key,unsigned int * amount);
Node * add_elem(Node * node, Node * elem);
void output_tree_s(Node * root,char * prefix,int is_left);
int travel(Node *root,unsigned int key);
Node *search(Node *root, unsigned int key);
Node *search_min(Node *root, unsigned int * key_it);
int del_elem(Tree * tree, unsigned int key, unsigned int rel);
Tree * read_f_file(int * error);
int graph(Tree * tree);
#endif // TREE_H_INCLUDED