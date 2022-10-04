#include <stdio.h>
#include <stdlib.h>
typedef enum bool{ true = 1 ,false = 0 }bool;
typedef struct node
{
	int data;
	struct node *next;
	struct node *previous;
}node;

void print_node(node *head)
{
	printf("previous:%p data:%d next:%p\n", head->previous, head->data, head->next);
}

node *alloc_node()
{
	node *newnode = malloc(sizeof(struct node));
	newnode->data = 0;
	newnode->next = NULL;
	newnode->previous = NULL;
	return newnode;
}

node *find_node(node *head, int data)
{
	while (true)
	{
		if (head->data==data)
		{
			return head;
		}
		head = head->next;
	}
}

void update_node(node *head, int data, int newdata)
{
	node *temp =find_node(head, data);
	temp->data = newdata;
}

int delete_node(node **head, int data)
{
	node *temp;
	node *original_head=(*head);
	temp = *head;

	if (temp->data==data)
	{
		*head = (*head)->next;
		(*head)->previous = NULL;
		free(temp);
		return 0;
	}

	while (true)
	{

		if ((*head)->next == NULL)
		{
			return -1;
		}
		if ((*head)->next->data==data)
		{
			temp = (*head);
			temp = temp->next;
			if (temp->next!=NULL)
			{
				node *node_next = temp->next;
				(*head)->next = node_next;
				node_next->previous = (*head);
				(*head) = original_head;
				free(temp);
				return 0;
			}
			(*head)->next = NULL;
			(*head) = original_head;
			free((temp));
			return 0;
		}

		(*head) = (*head)->next;
	}

}

node *add_head(node *head, int data)
{
	node *new_head = alloc_node();
	new_head->data = head->data;
	new_head->next = head->next;
	head->next = new_head;
	new_head->previous = head;
	head->data = data;
	
	return new_head;
}

node *add_tail(node *head, int data)
{
	node *new_tail = alloc_node();
	while (true)
	{
		if (head->next == NULL)
		{
			head->next = new_tail;
			new_tail->previous = head;
			new_tail->data = data;
			return new_tail;
			break;
		}
		head = head->next;
	}
}

void add_mid(node *head, int prev, int next, int data)
{
	node *temp_prev = find_node(head,prev);
	node *temp_next = find_node(head,next);
	node *new_mid = alloc_node();
	temp_prev->next = new_mid;
	new_mid->data = data;
	new_mid->previous = temp_prev;
	new_mid->next = temp_next;
	temp_next->previous = new_mid;
}



void print_list(node *head)
{
	while (true)
	{
		print_node(head);
		if (head->next==NULL)
		{
			break;
		}
		head = head->next;
	}
}


void print_reverse_with_prev(node *head)//with using the previous pointer
{
	node *tail = head;
	while (true)
	{
		if (tail->next == NULL)
		{
			break;
		}
		tail = tail->next;
	}
	
	while (true)
	{
		print_node(tail);
		if (tail==head)
		{
			//print_node(tail);
			break;
		}
		tail = tail->previous;
	}
}


void print_reverse(node *head)//without using the previous pointer
{
	node *original_head_value = head;
	node *temp = head;
	while (true)
	{
		if (head->next == temp)
		{
			temp = head;
			print_node(temp);

			head = original_head_value;
		}
		if (original_head_value->next == temp)
		{
			print_node(original_head_value);
			break;
		}

		head = head->next;

		if (head->next == NULL)
		{
			temp = head;
			print_node(temp);
			head = original_head_value;
		}

	}
}

int main()
{
	node *head = alloc_node();
	head->data = 78;

	add_head(head,32);
	print_list(head);
	printf("\n\n\n");
	add_tail(head,45);
	print_list(head);
	printf("\n\n\n");
	add_mid(head,32,78,99);
	print_list(head);
	printf("\n\n\n");
	print_reverse_with_prev(head);
	printf("\n\n\n");
	update_node(head,45,445);
	print_list(head);
	printf("\n\n\n");
	delete_node(&head,32);
	print_list(head);
	printf("\n\n\n");
}





