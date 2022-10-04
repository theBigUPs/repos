#include <stdio.h>
#include <stdlib.h>


void copy_array(int *dest,int *source, int length)
{
	for (size_t i = 0; i < length; i++)
	{
		dest[i] = source[i];
	}
}

void print_array(int *arr, int length)
{
	for (size_t i = 0; i < length; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}


int get_digit(int n, int digit)
{
	int mod;
	for (size_t i = 0; i < digit; i++)
	{
		mod = n % 10;
		n = n/10;
	}
	return mod;
}

int get_digit_count(int n)
{
	size_t i = 0;
	for (; n > 0; i++)
	{
		n = n / 10;
	}
	return i;
}


int get_biggest(int *arr, int length)
{
	int biggest = 0;
	for (size_t i = 0; i < length; i++)
	{
		if (arr[i]>biggest)
		{
			biggest = arr[i];
		}
	}
	return biggest;
}



void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int *L= malloc(sizeof(int)*n1);
	int *R = malloc(sizeof(int)*n2);


	for (i = 0; i < n1; i++)
	{
		L[i] = arr[l + i];
	}
	for (j = 0; j < n2; j++)
	{
		R[j] = arr[m + 1 + j];
	}


	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) 
	{
		if (L[i] <= R[j]) 
		{
			arr[k] = L[i];
			i++;
		}
		else 
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) 
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) 
	{
		arr[k] = R[j];
		j++;
		k++;
	}

}

void merge_sort(int arr[], int l, int r)
{
	r--;
	if (l < r) 
	{
		int m = l + (r - l) / 2;

		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}



partition(int *arr,int low,int high)
{
	int pivot = arr[(high+low)/2];
	int i = low - 1;
	int j = high + 1;
	for (;;)
	{
		do
		{
			i++;
		} while (arr[i]<pivot);

		do
		{
			j--;
		} while (arr[j]>pivot);

		if (i>=j)
		{
			return j;
		}
		int t = arr[i];
		arr[i]=arr[j];
		arr[j] = t;

	}
}


int  *quick_sort(int *arr, int low , int high)
{
	high--;
	if (low<high)
	{
		int p = partition(arr,low,high);
		quick_sort(arr,low,p);
		quick_sort(arr,p+1,high);
	}
	return arr;
}


void counting_sort(int *arr, int length)
{
	int counted[10] = { 0,0,0,0,0,0,0,0,0,0 };
	for (size_t i = 0; i < length; i++)
	{
		counted[arr[i]]++;
	}

	size_t j = 0;
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t k = 0;k < counted[i]; k++)
		{
			arr[j++] = i;
		}
	}
}



void radix_sort(int *arr, int length)
{
	int *output = malloc(sizeof(int)*length);
	int digits = get_digit_count(get_biggest(arr,length));
	int current_digit = 1;

	for (size_t j = 0; j < digits; j++)
	{
		int count[10] = { 0,0,0,0,0,0,0,0,0,0 };
		for (size_t i = 0; i < length; i++)
		{
			count[get_digit(arr[i],current_digit)]++;
		}

		for (size_t i = 0; i < 9; i++)
		{
			count[i + 1] = count[i]+count[i + 1];
		}

		for (int i = length-1; i >= 0; i--)
		{
			count[get_digit(arr[i], current_digit)]--;
			int index = count[get_digit(arr[i], current_digit)];
			output[index]=arr[i];
		}

		
		copy_array(arr,output,length);
		current_digit++;
	}
}




int main()
{
	int arr[] = { 12,8,78,3,5,16,23,91,33,6,17,45,44,25,20,10,678 };
	print_array(arr,17);
	//merge_sort(arr,0,17);
	//quick_sort(arr,0,17);
	radix_sort(arr,17);
	print_array(arr, 17);

}