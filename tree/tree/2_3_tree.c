//#include <stdio.h>
//#include <stdlib.h>
//
//
//typedef enum { false, true }bool;
//
//
//
//typedef struct tree
//{
//	int datalow;
//	int datahigh;
//	struct tree *left;      
//	struct tree *mid;
//	struct tree *right;
//}tt_tree;
//
//
//
//int findmid(int a, int b, int c)
//{
//	int mini = min(min(a, b), c);
//	int maxi = max(max(a, b), c);
//	int mid = a + b + c - maxi - mini;
//	return mid;
//}
//
//
//
//tt_tree *new_ttnode()
//{
//	tt_tree *new = malloc(sizeof(struct tree));
//
//	new->datahigh = -1;
//	new->datalow = -1;
//	new->left = NULL;
//	new->mid = NULL;
//	new->right = NULL;
//
//	return new;
//}
//
//
//tt_tree *findparent_ttnode(tt_tree *root, int data)
//{
//	/*if ((root->left->datalow == data || root->left->datahigh == data)||(root->right->datalow == data || root->right->datahigh == data)||(root->mid->datalow==data || root->mid->datalow == data))
//	{
//		return root;
//	}
//	else if (root->datalow < data < root->datahigh)
//	{
//		findparent_ttnode(root->mid, data);
//
//	}
//	else if (root->datalow>data)
//	{
//		findparent_ttnode(root->left, data);
//	}
//	else
//	{
//		findparent_ttnode(root->right, data);
//	}*/
//	return NULL;
//}
//
//
////tt_tree *insert_ttnode(tt_tree *root, int data)
////{
//	/*if (root==NULL)
//	{
//		tt_tree *newnode = new_ttnode();
//		newnode->datahigh = data;
//		return newnode;
//	}
//	else 
//	{
//
//		if (root->left == NULL && root->right == NULL && root->mid == NULL)
//		{
//			if (root->datahigh == -1)
//			{
//				if (root->datalow < data)
//				{
//					root->datahigh = data;
//				}
//				else
//				{
//					root->datahigh = root->datalow;
//					root->datalow = data;
//				}
//			}
//			else if (root->datalow == -1)
//			{
//				if (root->datahigh < data)
//				{
//					root->datalow = root->datahigh;
//					root->datahigh = data;
//				}
//				else
//				{
//					root->datalow = data;
//				}
//			}
//			else if (findparent_ttnode(root)!=NULL)
//			{
//				tt_tree *parent = findparent_ttnode(root);
//				if (parent->datalow==-1)
//				{
//					int middle = findmid(root->datahigh, root->datalow, data);
//					int mini = min(min(root->datahigh, root->datalow), data);
//					int maxi = max(max(root->datahigh, root->datalow), data);
//
//				}
//			}
//			else
//			{
//				int middle = findmid(root->datahigh, root->datalow, data);
//				int mini = min(min(root->datahigh, root->datalow), data);
//				int maxi = max(max(root->datahigh, root->datalow), data);
//				root->datahigh = middle;
//				root->datalow = -1;
//				root->left = new_ttnode();
//				root->left->datahigh = mini;
//				root->right = new_ttnode();
//				root->right->datahigh = maxi;
//			}
//			return root;
//		}
//
//		if (data > root->datahigh)
//		{
//			root->right = insert_ttnode(root->right, data);
//
//		}
//		else
//		{
//			root->left = insert_ttnode(root->left, data);
//		}
//
//	}
//	return root;
//}*/
//
//
//
//tt_tree *insert_ttnode2(tt_tree *root, int data)
//{
//
//
//
//	if (root == NULL)
//	{
//		tt_tree *newnode = new_ttnode();
//		newnode->datalow = data;
//		return newnode;
//	}
//
//
//
//
//	if (root->datahigh == -1)//case 1 node with only one data element
//	{
//		if (data>root->datalow)
//		{
//			root->datahigh = data;
//		}
//		else
//		{
//			root->datahigh = root->datalow;
//			root->datalow = data;
//		}
//
//		return root;
//
//	}
//	if (root->datalow == -1) 
//	{
//		if (data > root->datahigh)
//		{
//			root->datalow = root->datahigh;
//			root->datahigh = data;
//		}
//		else
//		{
//			root->datalow = data;
//		}
//
//		return root;
//	}
//	
//
//
//
//
//	if (data < root->datalow && root->datalow != -1 && root->left != NULL)
//	{
//		root->left = insert_ttnode2(root->left, data);
//
//	}
//	else
//	{
//		if (root->datahigh != -1 && data > root->datahigh)
//		{
//			root->right = insert_ttnode2(root->right, data);
//		}
//		if (root->datahigh == -1 && data > root->datalow)
//		{
//			root->right = insert_ttnode2(root->right, data);
//		}
//	}
//
//
//
//	tt_tree *parent = findparent_ttnode(root, data);
//
//	if (parent!=NULL &&(parent->datahigh == -1 || parent->datalow == -1) )//case2   node with 2 data elements parent contains 1
//	{
//		if (parent->right == root)
//		{
//			int mid = findmid(root->datahigh, root->datalow, data);
//			int mini = min(min(root->datahigh, root->datalow), data);
//			int maxi = max(max(root->datahigh, root->datalow), data);
//
//			parent->datahigh = mid;
//			
//			root->datalow = maxi;
//			root->datahigh = -1;
//			
//
//			parent->mid = insert_ttnode2(parent->mid,mini);
//
//		}
//		else
//		{
//			int mid = findmid(root->datahigh, root->datalow, data);
//			int mini = min(min(root->datahigh, root->datalow), data);
//			int maxi = max(max(root->datahigh, root->datalow), data);
//
//			parent->datahigh = parent->datalow;
//			parent->datalow = mid;
//			root->datalow = mini;
//			root->datahigh = -1;
//
//			parent->mid = insert_ttnode2(parent->mid, maxi);
//
//		}
//
//		
//
//	}
//	else if(parent != NULL) //case3  has 2 datan elements parent also has 2 data elements
//	{
//		tt_tree *newright = new_ttnode();
//		tt_tree *newleft = new_ttnode();
//
//
//		if (parent->left == root)
//		{
//
//			int midroot = findmid(root->datahigh, root->datalow, data);
//			int miniroot = min(min(root->datahigh, root->datalow), data);
//			int maxiroot = max(max(root->datahigh, root->datalow), data);
//
//			int midparent = findmid(midroot, parent->datahigh, parent->datalow);
//			int miniparent = min(min(parent->datahigh, parent->datalow), midparent);
//			int maxiparent = max(max(root->datahigh, root->datalow), midparent);
//
//			
//			newleft->datalow = miniparent;
//			newright->datalow = maxiparent;
//			parent->datalow = midparent;
//			parent->datahigh = -1;
//
//			newleft->left = root;
//			parent->left = newleft;
//			root->datalow = miniroot;
//			root->datahigh = -1;
//			newright->right = parent->right;
//			newright->left = parent->mid;
//			parent->mid = NULL;
//
//			parent->left = newleft;
//			parent->right = newright;
//
//			newleft->right = insert_ttnode2(newleft->right, maxiroot);
//
//		}
//
//	}
//}
//
//
//
//tt_tree *delete_ttnode(tt_tree *root)
//{
//	return root;
//}
//
//tt_tree *update_ttnode(tt_tree *root)
//{
//	return root;
//}
//
//
//int main()
//{
//
//	tt_tree *root = new_ttnode();
//	root->datalow = 5;
//
//	insert_ttnode2(root, 2);
//	insert_ttnode2(root, 6);
//	insert_ttnode2(root, 9);
//
//
//	printf("working\n\n");
//
//
//}
//
