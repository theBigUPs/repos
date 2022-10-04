//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct tree
//{
//	int data;
//	int height;
//	struct tree *left;
//	struct tree *right;
//}avl_tree;
//
//
//struct avl_tree *new_tree(int data)
//{
//	avl_tree *newtree = malloc(sizeof(struct tree));
//	newtree->right = NULL;
//	newtree->left = NULL;
//	newtree->data = data;
//	newtree->height = 1;
//	return newtree;
//}
//
//int tree_balance(avl_tree *root)
//{
//	if (root==NULL)
//	{
//		return 0;
//	}
//	return tree_height(root->left) - tree_height(root->right);
//}
//
//
//avl_tree *find(avl_tree *root, int data)
//{
//	if (root != NULL)
//	{
//		if (root->data == data)
//		{
//			return root;
//		}
//		else if (root->data > data)
//		{
//			find(root->left, data);
//		}
//		else
//		{
//			find(root->right, data);
//		}
//	}
//	else
//	{
//		return NULL;
//	}
//}
//
//int min_value(avl_tree *root)
//{
//	if (root==NULL)
//	{
//		return 0;
//	}
//	while (root->left != NULL)
//	{
//		root = root->left;
//	}
//	return root->data;
//}
//
//int tree_height(avl_tree *root)
//{
//	if (root==NULL)
//	{
//		return -1;
//	}
//	else
//	{
//		int lefth = 0;
//		int righth = 0;
//		lefth = tree_height(root->left);
//		righth = tree_height(root->right);
//		if (righth>lefth)
//		{
//			return righth + 1;
//		}
//		else
//		{
//			return lefth + 1;
//		}
//	}
//}
//
//avl_tree *rotate_right(avl_tree *node)
//{
//	avl_tree *t = node->left;
//	node->left = t->right;
//	t->right = node;
//	node->height = max(tree_height(node->left), tree_height(node->right))+1;
//	t->height = max(tree_height(t->left),tree_height(t->right))+1;
//	return t;
//}
//
//avl_tree *rotate_left(avl_tree *node)
//{
//	avl_tree *t = node->right;
//	node->right = t->left;
//	t->left = node;
//	node->height = max(tree_height(node->left), tree_height(node->right)) + 1;
//	t->height = max(tree_height(t->left), tree_height(t->right)) + 1;
//	return t;
//}
//
//avl_tree *rotate_rightleft(avl_tree *node)
//{
//	node->right = rotate_right(node->right);
//	return rotate_left(node);
//
//}
//
//avl_tree *rotate_leftright(avl_tree *node)
//{
//	node->left = rotate_left(node->left);
//	return rotate_right(node);
//}
//
//avl_tree *insert_avlnode(avl_tree *root, int data)
//{
//	if (root != NULL)
//	{
//		if (data < root->data)
//		{
//			root->left = insert_avlnode(root->left, data);
//
//		}
//		else if (data > root->data)
//		{
//			root->right = insert_avlnode(root->right, data);
//		}
//		else
//		{
//			return root;
//		}
//
//		root->height = max(tree_height(root->left), tree_height(root->right)) + 1;
//
//		if ((tree_height(root->left) - tree_height(root->right) > 1) && data < root->left->data)
//		{
//			return rotate_right(root);
//		}
//
//		if ((tree_height(root->left) - tree_height(root->right)) > 1 && data > root->left->data)
//		{
//			return rotate_leftright(root);
//		}
//
//		if ((tree_height(root->left) - tree_height(root->right)) < -1 && data > root->right->data)
//		{
//			return rotate_left(root);
//		}
//
//		if ((tree_height(root->left) - tree_height(root->right)) < -1 && data < root->right->data)
//		{
//			return rotate_rightleft(root);
//		}
//
//	}
//	else
//	{
//		root = new_tree(data);
//	}
//	return root;
//}
//
//
//avl_tree *delete_avlnode(avl_tree *root, int data)
//{
//	if (root == NULL)
//		return root;
//	if (data < root->data) 
//	{
//
//		root->left = delete_avlnode(root->left, data);
//
//	}
//
//
//	else if (data > root->data) 
//	{
//
//		root->right = delete_avlnode(root->right, data);
//
//	}
//
//
//	else 
//	{
//
//		if ((root->left == NULL) || (root->right == NULL)) 
//		{
//
//			avl_tree *t = root->left ? root->left : root->right;
//			
//			if (t == NULL) 
//			{
//
//				t = root;
//				root = NULL;
//
//			}
//			else 
//			{
//
//				*root = *t;
//
//			}
//
//			free(t);
//
//		}
//		else 
//		{
//
//			avl_tree *temp = min_value(root->right);
//		
//			root->data = temp->data;
//		
//			root->right = delete_avlnode(root->right, temp->data);
//			
//		}
//	}
//
//	if (root == NULL)
//	{
//
//		return root;
//
//	}
//	
//	root->height = max(tree_height(root->left), tree_height(root->right)) + 1;
//	
//
//	if (tree_balance(root) > 1 && tree_balance(root->left) >= 0)
//	{
//		
//		return rotate_right(root);
//
//	}
//
//
//	if (tree_balance(root) > 1 && tree_balance(root->left) < 0)
//	{
//
//		root->left = rotate_left(root->left);
//		return rotate_right(root);
//
//	}
//	
//	if (tree_balance(root) < -1 && tree_balance(root->right) <= 0)
//	{ 
//
//		return rotate_left(root);
//
//	}
//		
//	if (tree_balance(root) < -1 && tree_balance(root->right) > 0) 
//	{
//
//		root->right = rotate_right(root->right); 
//		return rotate_left(root);
//
//	}
//
//	return root;
//
//}
//
//
//avl_tree *update_avlnode(avl_tree *root, int from, int to)
//{
//
//	delete_avlnode(root, from);
//	insert_avlnode(root, to);
//	
//}
//
//int traverse_ldr(avl_tree *t)
//{
//	if (t == NULL)
//	{
//		return 0;
//	}
//	traverse_ldr(t->left);
//	printf("%d ", t->data);
//	traverse_ldr(t->right);
//	return 1;
//}
//
////int main()
////{
////
////
////	avl_tree *root = new_tree(14);
////	
////		int test[14] = {4,15,3,9,14,18,7,9,16,20,5,17,4,5};
////	
////		for (size_t i = 0; i < 14; i++)
////		{
////			insert_avlnode(root,test[i]);
////		}
////
////
////		traverse_ldr(root);
////		printf("\n\n\n\n");
////
////
////		delete_avlnode(root,5);
////
////
////		traverse_ldr(root);
////		printf("\n\n\n\n");
////
////
////		update_avlnode(root, 15, 1655);
////
////
////		traverse_ldr(root);
////		printf("\n\n\n\n");
////	
////	
////}
//
//
//
//
//
//
//
