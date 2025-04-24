/*******************************************************************************************************************************************************************
*Title		 		: Searching
*Description		: This function performs searching of the given data from the given Red Black tree.
*Prototype			: int search_tree(tree_t *root, data_t data); 
*Input Parameters	: root – Pointer to the root node of the Red Black tree.
					: item – Data to be searched from the Red Black tree.
*Output				: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include"rbt.h"

int search_tree(tree_t *root, data_t data)
{
    if(root==NULL)
    {
        printf("Tree is empty\n");
        return FAILURE;
    }

    while (root)
    {
        if(data < root->data)
        {
            root = root->left;
        }
        else if(data > root->data)
        {
            root = root->right;
        }
        else
        {
            printf("Data found in RB tree\n");
            return SUCCESS;
        }
    }
    
    printf("Element not found in tree\n");
    return FAILURE;
}