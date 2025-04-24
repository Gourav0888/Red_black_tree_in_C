/*******************************************************************************************************************************************************************
*Title				: Insertion
*Description		: This function performs inserting the new data into the given Red Black tree.
*Prototype			: int insert(tree_t **root, data_t item);
*Input Parameters	: root – Pointer to the root node of the Red Black tree.
					: item – New data to be inserted into the Red Black tree.
*Output				: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "rbt.h"

tree_t* create_node(data_t data)
{
	tree_t *new = (tree_t*)malloc(sizeof(tree_t));
	if(!new) return NULL;
	new->data = data;
	new->left = new->right = new->parent = NULL;
	//new node color always red
	new->color = RED;
	return new;
}

int insert(tree_t **root, data_t item)
{
	//create new node
	tree_t *new_node = create_node(item);
	if(!new_node) return FAILURE;

	//tree empty
	if(*root==NULL)
	{
		//root color always black
		new_node->color = BLACK;
		//no parent for root node
		new_node->parent = NULL;
		*root = new_node;
		printf("\nFirst node, no balancing required\nRB Tree-->\n");
		print_tree(*root);
		return SUCCESS;
	}

	//normal BST insertion
	tree_t *temp = *root, *parent=NULL;
	char flag=0;  //0(left) and 1(right)

	while (temp)
	{
		parent = temp;

		if(new_node->data > temp->data)
		{
			flag = 1;
			temp = temp->right;
		}
		else if(new_node->data < temp->data)
		{
			flag = 0;
			temp = temp->left;
		}
		else
		{
			free(new_node);
			//duplicate data
			printf("Data %d is already present in tree\n", item);
			return FAILURE;
		}
	}

	if(flag==0) //left
	{
		parent->left = new_node;
		new_node->parent = parent;
	}
	else  //right
	{
		parent->right = new_node;
		new_node->parent = parent;
	}
	
	// printf("%p %p\n", root, &(*root));
	printf("RB Tree before balacing\n");
	print_tree(*root);
	fix_balance_RBtree(root, new_node);
	(*root)->color = BLACK;
	printf("\nRB Tree after balacing\n");
	print_tree(*root);
	return SUCCESS;
}

void fix_balance_RBtree(tree_t **root, tree_t *new_node)
{
	// check conditions untill new node become root node or it's parent is not BLACK
	while (new_node!=(*root) && new_node->parent->color==RED)
	{
		//new node parent's color is black then exit (do nothing)
		if(new_node->parent->color == BLACK)
			return;
		
		//new node parent's color is red
		if(new_node->parent->color == RED)
		{
			//check the color of new node parent's sibling (or uncle of new node)
			tree_t *grand_parent = new_node->parent->parent;
			tree_t *uncle;
			//find new node's uncle and store uncle in uncle pointer
			if(grand_parent->right == new_node->parent)
			{
				uncle = grand_parent->left;
			}
			else
			{
				uncle = grand_parent->right;
			}

			//check uncle's color
			if(uncle!=NULL && uncle->color == RED)
			{
				//uncle is RED
				
				//recolor new node's parent and uncle
				uncle->color = BLACK;
				new_node->parent->color = BLACK;

				//if new node's grandparent is root node then exit
				if(grand_parent==(*root))
					return;

				grand_parent->color = RED;

				//now grandparent is red, so check for its parent's color 
				new_node = grand_parent;
			}
			else if(uncle == NULL || uncle->color == BLACK)
			{
				//uncle is BLACK
				// printf("no uncle or black uncle\n");
				// print_tree(*root);
				// printf("\n");
				//do suitable rotations 
				//rotation conditions (LL, RR, RL, LR)

				//left left rotation (LL)
				//new node is at its parent's left and its parent is at left of its grandparent
				if (new_node == new_node->parent->left && new_node->parent == grand_parent->left)
				{
					// printf("LL\n");
					char tmp = new_node->parent->color;
					new_node->parent->color = grand_parent->color;
					grand_parent->color = tmp;

					tree_t* grand_parent_parent = grand_parent->parent;
					tree_t *new_subroot = right_rotation(grand_parent);

					if (grand_parent_parent)
					{
						if (grand_parent_parent->left == grand_parent)
							grand_parent_parent->left = new_subroot;
						else
							grand_parent_parent->right = new_subroot;
					}
					else
					{
						*root = new_subroot;
					}
					new_subroot->parent = grand_parent_parent;
					
				}
				//right right roatation (RR)
				//new node is at its parent's right and its parent is at right of its grandparent
			else if (new_node == new_node->parent->right && new_node->parent == grand_parent->right)
			{
				// printf("RR\n");
				// printf("gpc=%c pc=%c\n", grand_parent->color, new_node->parent->color);
				char tmp = new_node->parent->color;
				new_node->parent->color = grand_parent->color;
				grand_parent->color = tmp;
				// printf("gpc=%c pc=%c\n", grand_parent->color, new_node->parent->color);

				tree_t* grand_parent_parent = grand_parent->parent;
				// printf("gp_p=%p\n", grand_parent);
				tree_t *new_subroot = left_rotation(grand_parent);
				// printf("gp_p=%p\n", grand_parent);
				if (grand_parent_parent)
				{
					if (grand_parent_parent->left == grand_parent)
						grand_parent_parent->left = new_subroot;
					else
						grand_parent_parent->right = new_subroot;
				}
				else
				{
					*root = new_subroot;
				}
				new_subroot->parent = grand_parent_parent;
			}
				//left right rotation (LR)
				//new node is at its parent's right and its parent is at left of its grandparent
			else if (new_node == new_node->parent->right && new_node->parent == grand_parent->left)
			{
				// printf("LR\n");
				// printf("data=%d color=%c\n", new_node->parent->data,  new_node->parent->color);
				// printf("data=%d color=%c\n", grand_parent->data, grand_parent->color);
				// printf("gplp=%p\n", grand_parent->left->parent);
				grand_parent->left = left_rotation(new_node->parent);
				// printf("gplp=%p\n", grand_parent->left->parent);
				grand_parent->left->parent = grand_parent;
				// print_tree(*root);  
				// printf("\n");

				new_node->parent = grand_parent->left;
				// printf("data=%d color=%c\n", new_node->parent->data,  new_node->parent->color);
				// printf("data=%d color=%c\n", grand_parent->left->data, grand_parent->left->color);
				// printf("data=%d color=%c\n", grand_parent->data, grand_parent->color);
				char tmp = new_node->parent->color;
				new_node->parent->color = grand_parent->color;
				grand_parent->color = tmp;
				// printf("data=%d color=%c\n", new_node->parent->data,  new_node->parent->color);
				// printf("data=%d color=%c\n", grand_parent->data, grand_parent->color);

				tree_t* grand_parent_parent = grand_parent->parent;
				tree_t *new_subroot = right_rotation(grand_parent);

				if (grand_parent_parent)
				{
					if (grand_parent_parent->left == grand_parent)
						grand_parent_parent->left = new_subroot;
					else
						grand_parent_parent->right = new_subroot;
				}
				else
				{
					*root = new_subroot;
				}
				new_subroot->parent = grand_parent_parent;
			}
				//right left rotation (RL)
				//new node is at its parent's left and its parent is at right of its grandparent
			else if (new_node == new_node->parent->left && new_node->parent == grand_parent->right)
			{
				// printf("RL\n");
				grand_parent->right = right_rotation(new_node->parent);
				grand_parent->right->parent = grand_parent;
				new_node->parent = grand_parent->right;

				tree_t* grand_parent_parent = grand_parent->parent;
				char tmp = new_node->parent->color;
				new_node->parent->color = grand_parent->color;
				grand_parent->color = tmp;

				tree_t *new_subroot = left_rotation(grand_parent);

				if (grand_parent_parent)
				{
					if (grand_parent_parent->left == grand_parent)
						grand_parent_parent->left = new_subroot;
					else
						grand_parent_parent->right = new_subroot;
				}
				else
				{
					*root = new_subroot;
				}
				new_subroot->parent = grand_parent_parent;
			}

			}
		}
	}
	
}

tree_t* left_rotation(tree_t *root)
{
	tree_t* y = root;
	tree_t* x = y->right;
	tree_t* t3 = x->left;

	x->left = y;
	y->right = t3;

	x->parent = y->parent;
	y->parent = x;
	if (t3)
		t3->parent = y;

	return x; // new root of the rotated subtree
}

tree_t* right_rotation(tree_t *root)
{
	tree_t* x = root;
	tree_t* y = x->left;
	tree_t* t3 = y->right;

	y->right = x;
	x->left = t3;

	y->parent = x->parent;
	x->parent = y;
	if (t3)
		t3->parent = x;

	return y; // new root of the rotated subtree
} 