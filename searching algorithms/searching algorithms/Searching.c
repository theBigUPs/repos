#include <stdio.h>
#include <stdlib.h>

typedef enum {false ,true}bool;

typedef struct tree{
	struct tree *left_node;
	struct tree *right_node;
	int data;
}tree;


tree* new_node(int data)
{
	tree *new_tree_node = malloc(sizeof(struct tree));
	new_tree_node->data = data;
	new_tree_node->left_node = NULL;
	new_tree_node->right_node = NULL;

	return new_tree_node;
}


tree* insert(tree *root, int data)
{
	if (root!=NULL)
	{
		if (data < root->data)
			root->left_node = insert(root->left_node, data);

		else
			root->right_node = insert(root->right_node, data);
	}
	else 
	{
		root = new_node(data);
	}
	return root;
}


tree *binary_search(tree*root ,int data)
{
	if (root!=NULL)
	{
		if (root->data != data)
		{
			if (data < root->data)
				binary_search(root->left_node, data);

			else
				binary_search(root->right_node, data);
		}
		else if (root->data == data)
		{
			return root;
		}
	}
	else
		return NULL;
}


int seq_search(int arr[], int length, int data)
{
	int found = -1;
	for (size_t i = 0; i < length; i++)
	{
		if (arr[i]==data)
		{
			found = arr[i];
		}
	}
	return found;
}





int main()
{
	
	int arr[] = {1,55,78,123,6,9};



	printf("%d\n", seq_search(arr, 6, 123));



	tree *root = new_node(1);
	for (size_t i = 1; i < 6; i++)
	{
		insert(root, arr[i]);
	}
	printf("%d", binary_search(root, 123)->data);



}