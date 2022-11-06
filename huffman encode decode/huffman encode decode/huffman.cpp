#include<iostream>
#include <string>
#include <algorithm>
using namespace std;

typedef struct table
{
	string c;
	string bitpattern;
	int freq;
}table;

typedef struct tree 
{
	int total;
	string s;
	tree *left;
	tree *right;
}tree;

typedef struct node
{
	int freq;
	string c;
	node* next;
	node *left;
	node *right;

}node;


node *create_tree(node *queue)
{
	while (queue->next!=NULL)
	{
		node *tmp1 = queue;
		node *tmp2 = queue->next;

		

		queue = queue->next;
		if (queue->next!=NULL)
		{
			queue = queue->next;
		}
		
		tmp1->next = NULL;
		tmp2->next = NULL;

		node *n = new node;
		n->freq = tmp1->freq + tmp2->freq;
		n->c.append(tmp1->c);
		n->c.append(tmp2->c);

		if (tmp1->freq < tmp2->freq)
		{
			n->left = tmp1;
			n->right = tmp2;
		}
		else
		{
			n->left = tmp2;
			n->right = tmp1;
		}

		node *original = queue;
		node *prev = original;
		while (original->freq < n->freq)
		{
			prev = original;
			original->next;
		}
		n->next = original;
		prev->next = n;
		
	}
	


	return queue;
}


string encode(node *tree, string message)
{
	string huff = "";
	
	for (size_t i = 0; i < message.length(); i++)
	{
		node *t = tree;
		while ( t->left!=NULL && t->right!=NULL )
		{
			if (t->left->c.find(message[i]) != std::string::npos)
			{
				//found
				t = t->left;
				huff.append("0");
			}
			else
			{
				t = t->right;
				huff.append("1");
			}

		}
	}

	return huff;
}




string remove_all_instences_and_return_amount(string s,char c,int *freq)
{
	int k = 0;
	for (size_t i = 0; i < s.length(); i++)
	{
		if (s[i]==c)
		{
			s.erase(s.begin() + i);
			k++;
		}
	}
	*freq = k;
	return s ;
}


void sort_queue(node *t,int len)
{
	int i, j;
	for (i = 0; i < len - 1; i++)
	{
		// Last i elements are already in place
		for (j = 0; j < len - i - 1; j++)
		{
			
			if (t->freq > t->next->freq)
			{
				int kt;
				string ct;
				kt = t->freq;
				ct = t->c;
				
				
				t->freq = t->next->freq;
				t->c = t->next->c;

				t->next->freq = kt;
				t->next->c = ct;

			}
		}
	}
}



struct node* new_tree(int data, string s)
{
	node *new_tree = new node;
	new_tree->right = NULL;
	new_tree->left = NULL;
	new_tree->freq = data;
	new_tree->next = NULL;
	new_tree->c.append(s);
	return new_tree;
}


node *insert(node *root, int data, string s) {


	if (root==NULL)
	{
		node *new_tail = new_tree(data, s);
		return new_tail;
	}
	node *new_tail = new_tree(data,s);
	while (true)
	{
		if (root->next == NULL)
		{
			root->next = new_tail;
			
			new_tail->freq = data;
			return new_tail;
			break;
		}
		root = root->next;
	}
}



int main()
{



	string message = "hello";
	string msg2 =message;
	node *queue=NULL;
	int var = 0;
	int *freq = &var;
	int len = 0;
	node *queue2=queue;
	for (size_t i = 0; 0 < message.length(); i++)
	{
		string t = "";
		t += message[0];
		message = remove_all_instences_and_return_amount(message, message[0], freq);

		queue = insert(queue2,*freq,t);
		if (i==0)
		{
			queue2 = queue;
		}
		queue = queue2->next;
		len++;
	}
	queue = queue2;
	sort_queue(queue,len);


	create_tree(queue);

	string res = encode(queue, message);
	cout << res;
	////msg2.append("a");

	//tree *root = new tree;
	////root->s = "jhkjhkj";


	////std::string::difference_type n = std::count(message.begin(), message.end(), message[0]);
	////std::cout << message+"  kljdshfkljdshf   "+msg2;
	//
}