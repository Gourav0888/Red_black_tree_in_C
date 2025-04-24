#include"rbt.h"

int print_tree(tree_t *root)
{
    // printf("print\n");
    if(root!=NULL)
    {
        // printf("not null\n");
        print_tree(root->left);
        printf("Data = %d ", root->data);
        printf("(%s)\n", (root->color==RED ? "Red" : "Black"));
        print_tree(root->right);
    }
}