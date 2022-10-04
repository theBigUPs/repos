#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 5
typedef enum {false, true}bool;
typedef struct {
	int data;
	struct node *next;
}node;
typedef struct{
	node *top;
	int count;
}stack ;
bool empty(stack *stck){
	return (stck->count == 0);
}
bool full(stack *stck){
	return (stck->count==STACK_SIZE);
}
void push(stack *stck, int c){
	if (full){
		node *temp = (struct node *)malloc(sizeof(node));
		temp->data = c;
		temp->next = stck->top;
		stck->top = temp;
		stck->count++;
	}
	else{
		printf("stack full\n");
	}
}
int pop(stack *stck){
	node *temp = stck->top;
	stck->top = stck->top->next;
	int popped_data = temp->data;
	free(temp);
	stck->count--;
	return popped_data;
}
void init_stack(stack *stck){
	stck->top = NULL;
	stck->count = 0;
}
int main(){
	stack test;
	init_stack(&test);
	push(&test, 'h');
	push(&test, 'e');
	push(&test, 'l');
	push(&test, 'l');
	push(&test, 'o');
	for (size_t i = 0; i < 5; i++){
		printf("%c", pop(&test));
	}
	printf("\n\n");
}