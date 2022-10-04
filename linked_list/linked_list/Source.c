#include <stdio.h>
#include <stdlib.h>
typedef enum {false,true}bool;

typedef struct node{
	int data;
	struct node *next;
}node;




int main()
{
	node *head;
	node *neu;
	head = (node *)malloc(sizeof(node));
	neu = (node *)malloc(sizeof(node));
	
	head->data = 5;
	head->next = neu;
	neu->data = 36;
	neu->next = NULL;
	
	printf("%d  ",*(head->next));

}