#include <stdio.h>
#include <stdlib.h>

typedef enum { false ,true }bool;

typedef struct tree
{
	int data;
	struct tree *left;
	struct tree *right;
}tree;


struct tree* new_tree(int data)
{
	tree *new_tree = malloc(sizeof(struct tree));
	new_tree->right = NULL;
	new_tree->left = NULL;
	new_tree->data = data;
	return new_tree;
}


tree *insert(tree *root, int data) {
	
	if (root != NULL) {
		if (data < root->data) 
			root->left = insert(root->left, data);
		
		else
			root->right = insert(root->right, data);
	}
	else 
		root = new_tree(data);
	return root;
}




int traverse_dlr(tree *t)
{
	if (t == NULL)
	{
		return 0;
	}

	printf("%d ", t->data);
	traverse_dlr(t->left);
	traverse_dlr(t->right);
	return 1;
}


int traverse_ldr(tree *t)
{
	if (t == NULL)
	{
		return 0;
	}
	traverse_ldr(t->left);
	printf("%d ", t->data);
	traverse_ldr(t->right);
	return 1;
}


int traverse_lrd(tree *t)
{
	if (t == NULL)
	{
		return 0;
	}
	traverse_lrd(t->left);
	traverse_lrd(t->right);
	printf("%d ", t->data);
	return 1;
}



tree *find(tree *t, int data)
{
	if (t!=NULL)
	{
		if (t->data==data)
		{
			return t;
		}
		else if (t->data > data)
		{
			find(t->left, data);
		}
		else
		{
			find(t->right, data);
		}
	}
	else
	{
		return NULL;
	}
}

bool has_children(tree *t)
{
	if ((t->left != NULL) || (t->right != NULL))
	{
		return true;
	}
	else
	{
		return false;
	}
}


tree *succesor(tree *t)//succesor
{
	tree *successed = t;
	successed = successed->right;
	if (successed!=NULL)
	{
		while (true)
		{
			if (successed->left == NULL)
			{
				return successed;
			}
			else
			{
				successed = successed->left;
			}
		}
	}
	return t->left;
}


tree *predecesor(tree *root,int data)
{
	if ((root->left != NULL) )
	{
		if ((root->left->data == data))
		{
			return root;
		}
	}
	if ((root->right != NULL))
	{
		if ((root->right->data == data))
		{
			return root;
		}
	}
	
	if (root->data > data)
	{
		predecesor(root->left,data);

	}
	else
	{
		predecesor(root->right, data);
	}
	
}


int delet(tree *t, int data)
{
	tree *r = find(t, data);
	tree *tmp = NULL;
	int tmp_data = 0;

	if (r->left==NULL && r->right == NULL)//does not have a child
	{
		tmp = predecesor(t, r->data);

		if (tmp->left!=NULL )
		{
			if (tmp->left->data == r->data)
			{
				tmp->left = NULL;
			}
			
		}
		if(tmp->right != NULL)
		{
			if (tmp->right->data == r->data)
			{
				tmp->right = NULL;
			}
		}

		free(r);
		return 1;
	}
	else// has one child or two children
	{
		tmp = succesor(r);
		tmp_data = tmp->data;
		delet(t,tmp->data);
		r->data = tmp_data;
		
		return 1;
	}
	return 0;
}

//int delete_tree(tree *t, int data)
//{
//	tree *root = find(t, data);
//	tree *succesed = NULL;
//
//	if (has_children(root) == false)//has no children
//	{
//		succesed = succesor(t, data);
//		if (succesed->left == root)
//		{
//			succesed->left = NULL;
//		}
//		else
//		{
//			succesed->right = NULL;
//		}
//		free(root);
//		return 1;
//	}
//
//	else if ((root->left != NULL) && (root->right == NULL))//has one child in the left and the child is a leaf
//	{
//		if (!has_children(root->left))
//		{
//			root->data = root->left->data;
//			root->left = NULL;
//			free(root->left);
//			return 1;
//		}
//	}
//
//	else if ((root->left == NULL) && (root->right != NULL))//has one child in the right and the child is a leaf
//	{
//		if (!has_children(root->right))
//		{
//			root->data = root->right->data;
//			root->right = NULL;
//			free(root->right);
//			return 1;
//		}
//	}
//
//	else
//	{
//		succesed = find_parent(root);
//		root->data = succesed->data;
//		delete_tree(succesed, succesed->data);
//		return 1;
//	}
//	return 0;
//}



int depth(tree *t)
{
	int l ;
	int r ;
	if (t == NULL)
	{
		return 0;
	}
	r=depth(t->right);;
	
	l=depth(t->left);
	
	
	return r > l ? r+1 : l+1;

}

tree *min_value(tree *t)
{
	if (t == NULL)
	{
		return 0;
	}
	while (t->left != NULL)
	{
		t = t->left;
	}
	return t;
}

tree *max_value(tree *t)
{
	if (t == NULL)
	{
		return 0;
	}
	while (t->right != NULL)
	{
		t = t->right;
	}
	return t;
}

int main()
{

	tree *root = new_tree(14);

	int test[14] = {4,15,3,9,13,18,7,16,20,5,17};

	for (size_t i = 0; i < 11; i++)
	{
		insert(root,test[i]);
	}


	traverse_ldr(root);//inorder
	printf(" inorder\n\n\n");


	traverse_dlr(root);//preorder
	printf(" preorder\n\n\n");


	traverse_lrd(root);//postorder
	printf(" postorder\n\n\n");

	for (size_t i = 0; i < 11; i++)
	{
		delet(root, test[i]);
		traverse_ldr(root);//inorder
		printf(" inorder\n\n\n");
	}
		
		

	
	
	
	
	traverse_ldr(root);//inorder
	printf(" inorder\n\n\n");


	traverse_dlr(root);//preorder
	printf(" preorder\n\n\n");

	
	traverse_lrd(root);//postorder
	printf(" postorder\n\n\n");


	//tree *found = find(root, 5);
	//printf("data found %d\n\n\n",found->data);

	insert(root,99);
	
	traverse_ldr(root);//inorder
	printf(" inorder\n\n\n");


	traverse_dlr(root);//preorder
	printf(" preorder\n\n\n");


	traverse_lrd(root);//postorder
	printf(" postorder\n\n\n");


	printf("min value is %d\n", min_value(root)->data);

	printf("max value is %d\n", max_value(root)->data);

	printf("max depth is %d\n", depth(root));

	
	return 0;
}