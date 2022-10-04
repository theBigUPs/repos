#include <stdio.h>
#include<stdlib.h>

typedef struct graph
{
	int name;
	struct graph *points;

}graph;



void display_list(graph *head)
{
	for (;;)
	{
		printf("%c", head->name + 65);//+65 for letters
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
	graph *neo = malloc(sizeof(graph));
	neo->points = NULL;
	return neo;
}


void print_adjacency_list(graph *vertex[], int arr_length)
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

