/*******************************************************************************************************************************************************************
*Title			: Delete Minimum
*Description		: This function deletes the minimum data from the given Red Black tree.
*Prototype		: int delete_minimum(tree_t **root);
*Input Parameters	: root – Pointer to the root node of the Red Black tree.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "rbt.h"

int delete_minimum(tree_t **root)
{
	data_t min;
	if(find_minimum(*root, &min)==FAILURE)
		return FAILURE;
	printf("Min data is %d\n", min);
	delete(root, min);
	printf("Min data deleted successfully\n");
}
