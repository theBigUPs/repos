#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define STACK_SIZE 40

typedef enum { false, true }bool;
typedef struct {
	int data;
	struct node *next;
}node;
typedef struct {
	node *top;
	int count;
}stack;
bool empty(stack *stck) {
	return (stck->count == 0);
}
bool full(stack *stck) {
	return (stck->count == STACK_SIZE);
}
int top(stack *stck) {
	if (!empty(stck)) {
		return (stck->top->data);
	}
}
void push(stack *stck, int c) {
	if (!full(stck)) {
		node *temp = (struct node *)malloc(sizeof(node));
		temp->data = c;
		temp->next = stck->top;
		stck->top = temp;
		stck->count++;
	}
	else {
		printf("stack full\n");
	}
}
int pop(stack *stck) {
	if (!empty(stck)) 
	{
		node *temp = stck->top;
		stck->top = stck->top->next;
		int popped_data = temp->data;
		free(temp);
		stck->count--;
		return popped_data;
	}
	else
	{
		return -1;
	}
}
void init_stack(stack *stck) {
	stck->top = NULL;
	stck->count = 0;
}

void infix_to_postfix(char *arr1, char *arr2, int arr_size, stack *stck){
	int arr2count = 0;
	for (size_t i = 0; i < arr_size; i++){
		if ((arr1[i] != '-') && (arr1[i] != '+') && (arr1[i] != '*') &&
			(arr1[i] != '/') && (arr1[i] != '(') && (arr1[i] != ')') &&
			 (arr1[i] != '\0'))
		{
			arr2[arr2count] = arr1[i];
			arr2count++;
		}
		if (arr1[i] == '('){
			push(stck, arr1[i]);
		}
		if (arr1[i] == '*' || arr1[i] == '/'){
			push(stck, arr1[i]);
		}
		if (arr1[i] == '-' || arr1[i] == '+'){
			if (top(stck) == '/' || top(stck) == '*'){
				arr2[arr2count] = top(stck);
				arr2count++;
				pop(stck);
				push(stck, arr1[i]);
			}
			else{
				push(stck, arr1[i]);
			}
		}
		if (arr1[i] == ')'){
			while (top(stck) != '('){
				arr2[arr2count] = top(stck);
				arr2count++;
				pop(stck);
			}
			pop(stck);
		}
		if (arr1[i] == '\0'){
			while (!empty(stck)){
				arr2[arr2count] = top(stck);
				arr2count++;
				pop(stck);
			}
			break;
		}
	}
}


int postfix_calculator(char *testarr,int arr_size, stack *test){
	bool read_operand = false;
	char str[40] = "";
	int res = 0;
	for (int i = 0; i < arr_size; i++){
		int count = 0;
		int icount = i;
		while (testarr[icount] != '*'&& testarr[icount] != '/'&& testarr[icount] != '-' && testarr[icount] != '+' && testarr[icount] != ' ' && testarr[icount] != '\0'){
			read_operand = true;
			str[count] = testarr[icount];
			count++;
			icount++;
		}
		if (read_operand){
			read_operand = false;
			res = atoi(str);
			push(test, res);
			strcpy(str, "");
		}
		if (testarr[i] == '*'){
			int top1 = top(test);
			pop(test);
			int top2 = top(test);
			pop(test);
			top2 *= top1;
			push(test, top2);
		}
		if (testarr[i] == '/'){
			int top1 = top(test);
			pop(test);
			int top2 = top(test);
			pop(test);
			top2 /= top1;
			push(test, top2);
		}
		if (testarr[i] == '+'){
			int top1 = top(test);
			pop(test);
			int top2 = top(test);
			pop(test);
			top2 += top1;
			push(test, top2);
		}
		if (testarr[i] == '-'){
			int top1 = top(test);
			pop(test);
			int top2 = top(test);
			pop(test);
			top2 -= top1;
			push(test, top2);
		}
	}
	res = top(test);
	pop(test);
	return res;
}

int main() {
	stack test;
	init_stack(&test);
	char testarr[40] = "5 * (3 + 2)";  
	char result[40] = ""; 
	infix_to_postfix(testarr, result, 40, &test);
	int res = postfix_calculator(result,40,&test);
	printf("%d \n\n",res);
}


