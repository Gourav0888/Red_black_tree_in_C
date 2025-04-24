/*******************************************************************************************************************************************************************
*Title		 		: Deletion
*Description		: This function performs deleting of the given data from the given Red Black tree.
*Prototype			: int delete(tree_t **root, data_t item); 
*Input Parameters	: root – Pointer to the root node of the Red Black tree.
					: item – Data to be deleted from the Red Black tree.
*Output				: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "rbt.h"
int delete(tree_t **root, data_t item)
{
	if(*root==NULL)
	{
		printf("Tree is empty, No data to delete\n");
		return FAILURE;
	}

	if((*root)->left == NULL && (*root)->right==NULL)
	{
		free(*root);
		*root = NULL;
		printf("Data deleted successfully\n");
		return SUCCESS;
	}
	tree_t *node = *root;

	//serach item in RB Tree
	while (node!=NULL/* && (node->left!=NULL && node->right!=NULL)*/)
	{
		if(item < node->data)
			node = node->left;
		else if(item > node->data)
			node = node->right;
		else
		{
			if(node->right)
			{
				data_t min;
				find_minimum(node->right, &min);
				node->data = min;
				node = node->right;
				item = min;
			}
			else if(node->left)
			{
				data_t max;
				find_maximum(node->left, &max);
				node->data = max;
				node = node->left;
				item = max;
			}

			if(node->left==NULL && node->right==NULL)
				break;
		}
	}

	if(node==NULL)
	{
		printf("Data not found\n");
		return FAILURE;
	}

	// node->data = -1;
	// printf("DB data %d %c\n", node->data, node->color);

	fix_after_deletion(root, node);
	(*root)->color = BLACK;
	printf("Data deleted successfully\n");
	return SUCCESS;
}

void fix_after_deletion(tree_t **root, tree_t *db_node)
{
	int remove_flag=1;
	while (db_node != *root && db_node != NULL)
	{
		//check if node to delete if RED (if red just delete and return)
		if(db_node->color==RED)
		{
			tree_t *parent = db_node->parent;
			free(db_node);
			if (parent->left == db_node)
			{
				parent->left = NULL;
			}
			else
			{
				parent->right = NULL;
			}
			return ;
		}

		//store db_node sibling
		tree_t *db_node_sibling;
		if(db_node->parent->left == db_node)
			db_node_sibling = db_node->parent->right;
		else
			db_node_sibling = db_node->parent->left;

		//store db_node parent
		tree_t *parent = db_node->parent;


		//check db_node sibling color
		if(db_node_sibling->color==BLACK)
		{
			//sibling is BLACK and its bot children are also BLACK or NULL
			// printf("sibling is black\n");
			// printf("-------------------\n");
			// printf("sibling_Data2 = %d ", db_node_sibling->data);
			// printf("(%s)\n", (db_node_sibling->color==RED ? "Red" : "Black"));
			// printf("-------------------\n");
			if((db_node_sibling->left == NULL || db_node_sibling->left->color==BLACK ) && (db_node_sibling->right == NULL || db_node_sibling->right->color==BLACK))
			{
				// printf("sibling both child black\n");
				db_node_sibling->color = RED;
				if(remove_flag)
				{
					remove_flag = 0;
					free(db_node);
					if (parent->left == db_node)
					{
						parent->left = NULL;
					}
					else
					{
						parent->right = NULL;
					}
					db_node = NULL;
				}
				if(parent->color==BLACK)
					db_node = parent;
				else if(parent->color==RED)
					parent->color = BLACK;

				continue;
			}

			// printf("sib left %d %c\n", db_node_sibling->left->data, db_node_sibling->left->color);
			// printf("here1\n");
			//store db_node sibling's children
			tree_t *far_child, *near_child;

			//db_node is at parent's left 
			if(db_node == parent->left)
			{
				near_child = db_node_sibling->left;
				far_child = db_node_sibling->right;
			}
			//db_node is at parent's right
			else
			{
				near_child = db_node_sibling->right;
				far_child = db_node_sibling->left;
			}

			// printf("-------------------\n");
			// if(near_child!=NULL)
			// {
			// 	printf("near_Data = %d ", near_child->data);
			// 	printf("(%s)\n", (near_child->color==RED ? "Red" : "Black"));
			// }
			// printf("near done\n");
			
			// if(far_child!=NULL)
			// {
			// 	printf("far_Data = %d ", far_child->data);
			// 	printf("(%s)\n", (far_child->color==RED ? "Red" : "Black"));
			// }
			// printf("far done\n");
			// printf("-------------------\n");
			// printf("here2\n");
			//sibling is BLACK and sibling's child near to db_node is RED and far child is BLACK (or NULL) 
			if((near_child != NULL && near_child->color == RED) && (far_child==NULL || far_child->color==BLACK))
			{
				// printf("near is red and far is black or null\n");
				//swap colors of db_node's sibling and sibling's child which is near to db_node 
				char color = near_child->color;
				near_child->color = db_node_sibling->color;
				db_node_sibling->color = color;

				//rotate sibling opposite to db_node
				
				//if sibling is at left of parent then rotate it left
				if(parent->left = db_node_sibling)
				{
					parent->left = left_rotation(db_node_sibling);
				}
				//if sibling is at right of parent then rotate it right
				else
				{
					parent->right = right_rotation(db_node_sibling);
				}
				// print_tree(*root);
				// printf("---------------------\n");
				// printf("DB_Data = %d ", db_node->data);
				// printf("(%s)\n", (db_node->color==RED ? "Red" : "Black"));
				// printf("---------------------\n");
			}
			else if((far_child!=NULL && far_child->color == RED) && (near_child==NULL || near_child->color == BLACK))
			{
				// printf("far is red and near is black or null\n");
				//swap colors of db_node's parent and it's sibling
				char color = db_node_sibling->color;
				db_node_sibling->color = parent->color;
				parent->color = color;

				//rotate parent in db_node direction
				
				//db_node is at parent's left
				if(db_node == parent->left)
				{
					//left rotation

					//parent's parent is root 
					if(parent->parent==NULL)
					{
						*root = left_rotation(parent);
					}
					//parent's parent is not root
					else
					{
						if(parent == parent->parent->left)
						{
							parent->parent->left = left_rotation(parent);
						}
						else
						{
							parent->parent->right = left_rotation(parent);
						}
					}
				}
				//db_node is at parent's right
				else
				{
					//right rotation

					//parent's parent is root 
					if(parent->parent==NULL)
					{
						*root = right_rotation(parent);
					}
					//parent's parent is not root
					else
					{
						if(parent == parent->parent->left)
						{
							parent->parent->left = right_rotation(parent);
						}
						else
						{
							parent->parent->right = right_rotation(parent);
						}
					}
				}

				//remove db_node (make it NULL) and give its extra black to far_child
				if(remove_flag)
				{
					parent = db_node->parent;
					remove_flag = 0;
					free(db_node);
					if (parent->left == db_node)
					{
						parent->left = NULL;
					}
					else
					{
						parent->right = NULL;
					}
					db_node = NULL;
				}
				db_node = NULL;
				far_child->color = BLACK;
			}

		}
		else
		{
			//sibling is RED
			// printf("sibling is red\n");

			//swap colors of db_node's parent and it's sibling 
			char color = db_node_sibling->color;
			db_node_sibling->color = parent->color;
			parent->color = color;

			//rotate parent in db_node direction
			//if db_node is at left of parent
			// printf("before roatation\n");
			if(parent->left==db_node)
			{
				//left rotation
				if(parent->parent == NULL)
					*root = left_rotation(parent);
				else
					parent->parent->right = left_rotation(parent);
			}
			//if db_node is at right of parent 
			else
			{
				//right rotation
				if(parent->parent == NULL)
					*root = right_rotation(parent);
				else
					parent->parent->left = right_rotation(parent);
			}
			// printf("after rotation\n");
			// print_tree(*root);
		}

	}
	
}