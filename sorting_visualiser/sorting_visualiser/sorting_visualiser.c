#include <stdio.h>
#include <stdlib.h>
#define SIZE 20
#pragma warning(disable:4996)

//rand() % 20; 0 - 19


void swap(int *x, int *y)
{
	int t = 0;
	t = *x;
	*x = *y;
	*y = t;
}






void print_array(int arr[],int size,FILE *sort)
{

	fprintf(sort,"%s","---------------------------------------------------------------------------------------------------\n");
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < arr[i]; j++)
		{
			fprintf(sort,"%s","#");
		}
		fprintf(sort, "%s", "\n");
	}
	fprintf(sort, "%s", "---------------------------------------------------------------------------------------------------\n");
}



void bubble_sort(int arr[],int size,FILE *sort)
{
	for (size_t j = 0; j < size-1; j++)
	{
		for (size_t i = 0; i < (size- j - 1); i++)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(&arr[i], &arr[i + 1]);
				
			}
		}
		print_array(arr, size, sort);
	}
}



void fill_array(int arr[],int size)
{
	srand(time(NULL));
	int random_int ;
	for (size_t i = 0; i < size; i++)
	{
		random_int = (rand() % 50) + 1;
		arr[i] = random_int;
	}

}




int main()
{
	//1-50
	FILE *sort;
	sort = fopen("visualised.txt","w");



	int test[SIZE];

	fill_array(test,SIZE);
	

	print_array(test,SIZE,sort);

	bubble_sort(test,SIZE,sort);

	//print_array(test,SIZE);

	fclose(sort);
}