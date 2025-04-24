/***************************************************************************************************************************************************************
*Title		: This the header file for the Red Black Tree
****************************************************************************************************************************************************************/
#include<stdio.h>
#include<stdlib.h>

#ifndef RBT_H
#define RBT_H

#define SUCCESS   			  0
#define FAILURE 			 -1
#define RED			 		 'R'
#define BLACK		 	     'B'

#define INSERT			1
#define DELETE			2
#define FIND_MIN		3
#define DEL_MIN			4
#define FIND_MAX		5
#define DEL_MAX			6
#define SEARCH			7
#define DISPLAY			8
#define EXIT			9


typedef int data_t;

typedef struct node
{
	data_t data;
	char color;
	struct node *left;
	struct node *right;
	struct node *parent;
}tree_t;

/* keep all the prototypes of the functions here */

/*Delete element from RB tree*/
int delete(tree_t **root, data_t item);

/*Insert element from RB tree*/
int insert(tree_t **root, data_t item);

/*find minimum element from RB tree*/
int find_minimum(tree_t *root, data_t *min);

/*find maximum element from RB tree*/
int find_maximum(tree_t *root, data_t *max);

/*delete minimum element from RB tree*/
int delete_minimum(tree_t **root);

/*find maximum element from RB tree*/
int delete_maximum(tree_t **root);

/*print RB tree in inorder*/
int print_tree(tree_t *root);

/*left rotate tree*/
tree_t* left_rotation(tree_t *root);

/*right rotate tree*/
tree_t* right_rotation(tree_t *root);

/*Fix and balance RB tree after insertion*/
void fix_balance_RBtree(tree_t **root, tree_t *new_node); 

/*Fix and balance RB tree after deletion*/
void fix_after_deletion(tree_t **root, tree_t *new_node); 

/*Search data in tree*/
int search_tree(tree_t *root, data_t data);

#endif
