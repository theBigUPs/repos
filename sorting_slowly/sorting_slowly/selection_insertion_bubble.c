#include <stdio.h>


void swap(int *a , int *b)
{
	int t = 0;
	t = *a;
	*a = *b;
	*b = t;
}


int *selection(int arr[], int len)
{
	int counter = 0;
	for (size_t i = 0; i < len-1; i++)
	{
		int min_index = i;
		for (size_t j = i+1; j < len; j++)
		{
			if (arr[j]<arr[min_index])
			{
				min_index = j;
				counter++;
			}
		}
		swap(&arr[i],&arr[min_index]);

	}
	printf("completed in %d steps with selection sort\n",counter);
	return arr;
}



int *insertion(int arr[], int len)
{
	int counter = 0;
	for (size_t i = 1; i < len; i++)
	{
		int key = arr[i];
		size_t j = i - 1;
		for (; (j >= 0) && (key < arr[j]); j--)
		{
			swap(&arr[j + 1] , &arr[j]);
			counter++;
		}
	}
	printf("completed in %d steps with insertion sort\n", counter);
	return arr;
}  



int *bubble(int arr[], int len)
{
	int counter = 0;
	for (size_t i = 0; i < len-1; i++)
	{
		for (size_t j = i; j < len; j++)
		{
			if (arr[i]>arr[j])
			{
				swap(&arr[i], &arr[j]);
				counter++;
			}
		}
	}
	printf("completed in %d steps with bubble sort\n", counter);
	return arr;
}


void print_array(int arr[], int len)
{
	for (size_t i = 0; i < len; i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");

}


int main()
{
	int arr[10] = { 44,7,23,99,4,39,456,2,12,9 };
	print_array(arr, 10);
	//selection(arr,10);
	insertion(arr,10);
	//bubble(arr,10);
	print_array(arr, 10);
	
}