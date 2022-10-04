#include <stdio.h>
#include <stdlib.h>


typedef enum bool{ true = 1 ,false = 0 }bool;

typedef struct person
{
	char tc[12];
	char name[50];
}person;




typedef struct node
{
	person p;
	struct node *next;
}node;

bool isempty(node *n)
{
	if (n == NULL)
	{
		return true;
	}
	else
		return false;
}

node *allocate()
{
	node *neu = malloc(sizeof(struct node));
	//neu->p = NULL;
	neu->next = NULL;
	return neu;
}


node *find_node(node *head, char data[])
{
	for (;;)
	{
		if (head->p.tc == data)
		{
			return head;
		}
		if (head->next == NULL)
		{
			break;
		}
		head = head->next;
	}
}

void update_node(node *head, int data, int to)
{
	head = find_node(head, data);
	//head->p = to;
}


void delete_head(node **head)
{
	struct node *temp;

	if (head == NULL || *head == NULL) return;
	temp = *head;

	*head = (*head)->next;

	free(temp);
}


void delete_node(node *head, int data)
{
	node *temp = head;
	for (;;)
	{

		if (head->next == NULL)
		{
			break;
		}
		//if (head->next->p == data)
		{
			temp = head;
			head = head->next;
			temp->next = head->next;
			free(head);
			break;
		}

		head = head->next;
	}

}


void printnode(node *n)
{
	printf("%d p ->", n->p);
	printf("%p next\n", n->next);
}


void display_list(node *head)
{
	for (;;)
	{
		printnode(head);
		if (head->next == NULL)
		{
			break;
		}
		head = head->next;
	}
}



void add_head(node *head, int data)
{
	node *newhead = allocate();
	newhead->next = head->next;
	newhead->p = head->p;
	head->next = newhead;
	//head->p = data;
}


void add_last(node *head, int data)
{
	for (; head->next != NULL;)
	{
		head = head->next;
	}
	node *neu = allocate();
	head->next = neu;
	//neu->p = data;
}


void add_middle(node *head, int data1, int data2, int newdata)
{
	node *temp1 = find_node(head, data1);
	node *temp2 = find_node(head, data2);
	node *temp3 = allocate();
	//temp3->p = newdata;
	temp1->next = temp3;
	temp3->next = temp2;
}


node *find_tail(node *head)
{
	while (true)
	{
		head = head->next;
		if (head->next != NULL)
		{
			break;
		}
	}
	return head;
}

void print_reverse(node *head)
{
	node *original_head_value = head;
	node *temp = head;
	while (true)
	{
		if (head->next == temp)
		{
			temp = head;
			printnode(temp);

			head = original_head_value;
		}
		if (original_head_value->next == temp)
		{
			printnode(original_head_value);
			break;
		}

		head = head->next;

		if (head->next == NULL)
		{
			temp = head;
			printnode(temp);
			head = original_head_value;
		}

	}
}


void recrev(node *head)//recursively reverses the list
{
	if (head->next != NULL)
	{
		recrev(head->next);
	}
	printf("%d  ", head->p);
}









int hash(person p)
{
	int tot = 0;
	int index;
	for (size_t i = 0; i < 12; i++)
	{
		tot += p.tc[i];
	}
	index = tot % 99;
	return index;
}


int add(person p, node arr[])
{
	int index = hash(p);
	arr[index].next->next->p = p;
	return 0;
}

int main()
{
	
	node arr[100]; //this works and is the basis of the hashmap



	
}




