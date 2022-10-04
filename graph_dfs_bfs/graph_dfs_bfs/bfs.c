#include "graph.h"
#include "queue.h"
#define N 7

typedef enum color { white = 1, grey = 2, black = 3 }color;
//typedef enum bool{ false ,true }bool;

//int adj[N][N] = {
//					{1,1,1,1,1,1},
//					{1,1,1,1,1,1},
//					{1,1,1,1,1,1},
//					{1,1,1,1,1,1},
//					{1,1,1,1,1,1}
//};
//

int BFS(int *graph, int s)
{
	
}

int main()
{

	graph *vertex[N];


	for (size_t i = 0; i < N; i++)
	{
		vertex[i] = new_graph_node();
		vertex[i]->name = i;
	}


	add_edge(vertex[0], 1);
	add_edge(vertex[0], 2);
	add_edge(vertex[0], 3);

	add_edge(vertex[1], 3);
	add_edge(vertex[1], 4);

	add_edge(vertex[2], 5);

	add_edge(vertex[3], 2);
	add_edge(vertex[3], 5);
	add_edge(vertex[3], 6);

	add_edge(vertex[4], 3);
	add_edge(vertex[4], 6);

	add_edge(vertex[6], 5);

	print_adjacency_list(vertex, N);

}