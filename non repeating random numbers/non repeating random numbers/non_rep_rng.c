#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum bool{false ,true}bool;

int rng(int end)
{
	int num;
	num = rand();
	num = (num % end)+1;
	//printf("%d\t", num);
	return num;
}

bool contains(int arr[], int data, int length)
{
	for (size_t i = 0; i < length; i++)
	{
		if (arr[i]==data)
		{
			return true;
		}
	}
	return false;
}


int *nonrep(int end)
{
	int *arr = malloc(end*sizeof(int));
	int n = end;
	int index = 0;
	while (n)
	{
		int tmp = rng(end);
		if (contains(arr, tmp, end))
		{
			continue;
		}
		else
		{
			arr[index] = tmp;
			index++;
			n--;
		}
	}
	return arr;
}


int main()
{
	srand(time(0));

	int end = 10;
	int *arr = nonrep(end);
	for (size_t i = 0; i < end; i++)
	{
		printf("%d\t",arr[i]);
	}
	
}