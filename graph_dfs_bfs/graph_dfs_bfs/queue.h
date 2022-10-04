#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true }bool;

typedef struct node
{
	int data;
	struct node *next;
}queue;

queue *allocate()
{
	queue *neo = malloc(sizeof(struct node));
	neo->next = NULL;
	return neo;
}

queue *enqueue(queue *t, int key)
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
	return *t;
}

bool isempty(queue *t)
{
	if (t == NULL)
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
	while (q != NULL)
	{
		printf("%d ", q->data);
		q = q->next;
	}
	printf("\n");
}