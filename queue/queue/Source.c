#include <stdio.h>
#include <stdlib.h>

typedef enum {false,true}bool;

typedef struct node
{
	int data;
	struct node *next;
}queue;

queue *allocate()
{
	queue *new = malloc(sizeof(struct node));
	new->next = NULL;
	return new;
}

queue *enqueue(queue *t,int key)
{
	queue *neo = allocate();
	neo->data = t->data;
	neo->next = t->next;
	t->next = neo;
	t->data = key;
	return t;
}

queue *dequeue(queue **t)
{
	if (t == NULL || *t == NULL) return NULL;
	queue *neo = *t;
	*t = (*t)->next;
	free(neo);
	return t;
}

bool isempty(queue *t)
{
	if (t==NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void print_queue(queue *q)
{
	while (q!=NULL)
	{
		printf("%d ",q->data);
		q = q->next;
	}
	printf("\n");
}



int main()
{
	queue *head = allocate();
	head->data = 11;
	for (size_t i = 1; i < 10; i++)
	{
		enqueue(head,i);
	}
	print_queue(head);

	dequeue(&head);
	print_queue(head);

}





