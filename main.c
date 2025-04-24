/**************************************************************************************************************************************************************
*Name 			: Gourav Singh
*Batch			: 24021B
*Title			: main function(Driver function)
*Description	: This function is used as the driver function for the all the functions
***************************************************************************************************************************************************************/
#include "rbt.h"

int main()
{
	/* Declare the pointers */
	tree_t *root = NULL;
	data_t data;
	data_t minimum;
	data_t maximum;
	char option;
	int operation;

	// insert(&root, 50);
	// insert(&root, 20);
	// insert(&root, 65);
	// insert(&root, 15);
	// insert(&root, 35);
	// insert(&root, 1);
	// delete(&root, 1);
	// insert(&root, 55);
	// insert(&root, 70);
	// insert(&root, 68);
	// insert(&root, 80);
	// insert(&root, 90);

	do
	{
		/* Display the menu */
		printf("\n1. Insert Data\n2. Delete Data\n3. Find Minimum Data\n4. Delete Minimum Data\n5. Find Maximum Data\n6. Delete Maximum Data\n7. Search Data in Tree\n8. Display Tree\n9. Exit\n");

		/* Read the option for performing the operation */
		scanf("%d", &operation);
		/* Jump to the option entered by the user */
		switch (operation)
		{
			case INSERT:
				printf("Enter the data to be inserted into the RB Tree: ");
				scanf("%d", &data);
				insert(&root, data);
				/* Modify the above line to handle the error */
				// printf("tree\n");
				break;
			case DELETE:
				printf("Enter the data to be deleted from the RB Tree: ");
				scanf("%d", &data);
				delete(&root, data);
				/* Modify the above line to handle the error */
				print_tree(root);
				break;
			case FIND_MIN:
				if(find_minimum(root, &minimum)==SUCCESS)
				{
					printf("Minimum data: %d\n", minimum);
				}
				else
				{
					printf("Tree is empty\n");
				}
				// print_tree(root);
				break;
			case DEL_MIN:
				delete_minimum(&root);
				/* Modify the above line to handle the error */
				print_tree(root);
				break;
			case FIND_MAX:
				if(find_maximum(root, &maximum)==SUCCESS)
				{
					printf("Maximum data: %d\n", maximum);
				}
				else
				{
					printf("Tree is empty\n");
				}
				break;

			case DEL_MAX:
				delete_maximum(&root);
				/* Modify the above line to handle the error */
				print_tree(root);
				break;	

			case SEARCH:
				printf("Enter the data want to search in RB Tree: ");
				scanf("%d", &data);
				search_tree(root, data);
				break;

			case DISPLAY:
				if(root==NULL)
				{
					printf("RB Tree is empty\n");
				}
	            else
					print_tree(root);
				break;
			
			case EXIT:
				return 1;
			default:
				printf("Invalid Option...\nTry Again...\n");		
		}
	}while (1);

	return 0;
}
