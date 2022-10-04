#include <stdio.h>
#include<stdlib.h>

#define node_number 7


typedef struct graph 
{
	int name;
	struct graph *points;

}graph;



void display_list(graph *head)
{
	for(;;)
	{
		printf("%c", head->name+65);//+65 for letters
		if (head->points == NULL)
		{
			break;
		}
		printf(" -> ");
		head = head->points;
	}
}

graph *new_graph_node()
{
	graph *new = malloc(sizeof(struct graph));
	new->points = NULL;
	return new;
}


void print_adjacency_list(graph *vertex[],int arr_length)
{
	for (size_t i = 0; i < arr_length; i++)
	{
		display_list(vertex[i]);
		printf("\n");
	}
}


void add_edge(graph *head, int name)
{
	for (; head->points != NULL;)
	{
		head = head->points;
	}
	graph *neu = new_graph_node();
	head->points = neu;
	neu->name = name;
}

//int main()
//
//{
//
//
//	graph *vertex[node_number];
//
//
//	for (size_t i = 0; i < node_number; i++)
//	{
//		vertex[i] = new_graph_node();
//		vertex[i]->name = i;
//	}
//	
//
//	add_edge(vertex[0], 1);
//	add_edge(vertex[0], 2);
//	add_edge(vertex[0], 3);
//
//	add_edge(vertex[1], 3);
//	add_edge(vertex[1], 4);
//
//	add_edge(vertex[2], 5);
//
//	add_edge(vertex[3], 2);
//	add_edge(vertex[3], 5);
//	add_edge(vertex[3], 6);
//
//	add_edge(vertex[4], 3);
//	add_edge(vertex[4], 6);
//
//	add_edge(vertex[6], 5);
//
//	print_adjacency_list(vertex, node_number);
//	
//}
//
