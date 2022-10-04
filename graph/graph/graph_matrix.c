#include <stdio.h>
#include<stdlib.h>

#define node_number 6



void new_adjacency_matrix(int arr[][node_number])
{
	for (size_t i = 0; i < node_number; i++)
	{
		for (size_t j = 0; j < node_number; j++)
		{
			arr[i][j] = 0;
		}
	}
}



void addedge(int arr[][node_number],int i , int j)
{
	arr[i][j] = 1;
}



void print_2dmatrix(int arr[][node_number])
{
	for (size_t i = 0; i < node_number; i++)
	{
		for (size_t j = 0; j < node_number; j++)
		{
			printf("%d\t",arr[i][j]);
		}
		printf("\n\n");
	}
}



int main()
{
	int arr[node_number][node_number]; 
	new_adjacency_matrix(arr);

	addedge(arr, 0, 1);
	addedge(arr, 0, 4);
	//addedge(arr, 0, 3);


	addedge(arr, 1, 4);
	addedge(arr, 1, 0);
	addedge(arr, 1, 2);

	addedge(arr, 2, 4);
	addedge(arr, 2, 3);
	addedge(arr, 2, 5);

	addedge(arr, 3, 2);
	addedge(arr, 3, 4);
	addedge(arr, 3, 5);

	addedge(arr, 4, 0);
	addedge(arr, 4, 1);
	addedge(arr, 4, 2);
	addedge(arr, 4, 3);
	//addedge(arr, 4, 6);


	addedge(arr, 5, 2);
	addedge(arr, 5, 3);


	print_2dmatrix(arr);
}