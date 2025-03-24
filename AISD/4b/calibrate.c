#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "tools.h"
#include "dialog.h"
unsigned int height(Node * node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        return node->height;
    }
}
void fixheight(Node * node)
{
    unsigned int hi_left = height(node->left),hi_right = height(node->right);
    node->height = (hi_left > hi_right ? hi_left : hi_right) + 1;
}
Node* rotate_left(Node * node)
{
    Node * mem = node->right;
    node->right = mem->left;
    mem->left = node;
    fixheight(node);
    fixheight(mem);
    return mem;
}
Node* rotate_right(Node * node)
{
    Node * mem = node->left;
    node->left = mem->right;
    mem->right = node;
    fixheight(node);
    fixheight(mem);
    return mem;
}
int crtiter(Node * node)
{
    return height(node->right)-height(node->left);
}
Node* balance(Node * node)
{
    fixheight(node);
    if(crtiter(node) == 2)
    {
        if(crtiter(node->right) < 0)
        {
            node->right = rotate_right(node->right);
        }
        return rotate_left(node);
    }
    if(crtiter(node) == -2)
    {
        if(crtiter(node->left) > 0)
        {
            node->left = rotate_left(node->left);
        }
        return rotate_right(node);
    }
    return node;
}
