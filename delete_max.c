/*******************************************************************************************************************************************************************
*Title			: Delete Maximum
*Description		: This function deletes the maximum data from the given Red Black tree.
*Prototype		: int delete_maximum(tree_t **root);
*Input Parameters	: root – Pointer to the root node of the Red Black tree.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "rbt.h"

int delete_maximum(tree_t **root)
{
	data_t max;
	if(find_maximum(*root, &max)==FAILURE)
		return FAILURE;
	printf("Max data is %d\n", max);
	delete(root, max);
	printf("Max data deleted successfully\n");
}
