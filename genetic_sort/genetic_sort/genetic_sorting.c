#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef enum bool{false,true}bool;


typedef struct individual
{
	int *arr;
	int fitness;
}individual;


void print_array(int arr[], int length)
{
	for (size_t i = 0; i < length; i++)
	{
		printf("%d  ",arr[i]);
	}
	printf("\n");
}


int rng(int end)
{
	int num;
	num = rand();
	num = (num % end) + 1;
	//printf("%d\t", num);
	return num;
}


bool contains(int arr[], int data, int length)
{
	for (size_t i = 0; i < length; i++)
	{
		if (arr[i] == data)
		{
			return true;
		}
	}
	return false;
}


int mark(int arr[],int num, int arr_length) 
{
	for (size_t i = 0; i < arr_length; i++)
	{
		if (arr[i] == num)
		{
			arr[i] = -1;
			return 1;
		}
	}
}


int *non_repeating_random_numbers(int end)
{
	int *arr = malloc(end * sizeof(int));
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


individual *new_individual(int arr_length) 
{
	individual *tmp = malloc(sizeof(struct individual));
	tmp->arr = (int*)malloc(sizeof(int)*arr_length);
	tmp->fitness = 0;
	return tmp;
}


int get_fitness(individual *ind,  int arr_length) 
{
	int res = 0;
	for (size_t i = 0; i < arr_length; i++)
	{
		for (size_t j = i; j < arr_length; j++)
		{
			if (ind->arr[i]>ind->arr[j])
			{
				res++;
			}
		}

	}
	return res;
}


void mutate(individual *ind, int arr_length) 
{
	int first = -1;
	int firstindex;
	int second = -1;
	int secondindex;

	for (size_t i = 0; i < arr_length; i++)
	{
		if (rng(10)==5)
		{
			if (first != -1)
			{
				second = ind->arr[i];
				secondindex = i;
			}
			else 
			{
				first = ind->arr[i];
				firstindex = i;
			}
		}

		if ((first != -1) && (second != -1))
		{
			ind->arr[secondindex] = first;
			ind->arr[firstindex] = second;
			first = -1;
			second = -1;
		}
		
	}

}


int find_least_fit(individual *inds[], int ind_length) //returns the index of the least fit 
{


	int max = inds[0]->fitness;
	int leastindex = 0;
	for (int i = 1; i < ind_length; i++)
		if (inds[i]->fitness > max)
		{
			max = inds[i]->fitness;
			leastindex = i;
		}
	return leastindex;


}


int find_most_fit(individual *inds[], int ind_length) //returns the index of the most fit 
{
	int smallest = inds[0]->fitness;
	int inx = 0;

	for (int i = 1; i < ind_length; i++) 
	{
		if (inds[i]->fitness < smallest) 
		{
			smallest = inds[i]->fitness;
			inx = i;
		}
	}
	return inx;
}


void find_two_most_fit(individual *inds[], int ind_length, int *min1index, int *min2index)// returns the indexes of the two most fit
{
	int min1 = inds[0]->fitness;
	*min1index = 0;
	int min2 = inds[1]->fitness;
	*min2index = 1;
	if (min2 < min1)
	{
		min1 = inds[1]->fitness;
		*min1index = 1;
		min2 = inds[0]->fitness;
		*min2index = 0;
	}

	for (int i = 2; i < ind_length; i++)
	{
		if (inds[i]->fitness < min1)
		{
			min2 = min1;
			*min2index = *min1index;
			min1 = inds[i]->fitness;
			*min1index = i;
		}
		else if (inds[i]->fitness < min2)
		{
			min2 = inds[i]->fitness;
			*min2index = i;
		}
	}
}


individual *make_child(individual *frst, individual *scnd, int arr_length)
{
	individual *tmp = new_individual(arr_length);

	int intersect = rng(arr_length)-1;
	
	int *checker = (int*)malloc(sizeof(int)*arr_length);
	for (size_t k = 0; k < arr_length; k++)
	{
		checker[k] = scnd->arr[k];
	}

	for (size_t i = 0; i < intersect; i++)
	{
		tmp->arr[i] = frst->arr[i];
		mark(checker,tmp->arr[i],arr_length);
	}

	int count = intersect;
	for (size_t i = intersect; i < arr_length; i++)
	{
		while (checker[count] == -1)
		{
			count++;
			if (count >= arr_length)
			{
			count = 0;
			}
		}
		//while (contains(tmp->arr, scnd->arr[count], arr_length))
		//{
		//	count++;
		//	if (count >= arr_length)
		//	{
		//		count = 0;
		//	}
		//}
		tmp->arr[i] = checker[count];
		count++;
		if (count >= arr_length)
		{
			count = 0;
		}
	}
	mutate(tmp,arr_length);
	tmp->fitness = get_fitness(tmp,arr_length);
	return tmp;
}


void populate_array(individual *inds[], int arr[], int ind_length, int arr_length)
{
	
	for (size_t i = 0; i < ind_length; i++)
	{
		int *nonreps= non_repeating_random_numbers(arr_length);
		for (size_t j = 0; j < arr_length; j++)
		{
			inds[i]->arr[j] = arr[nonreps[j]-1];
		}
		inds[i]->fitness = get_fitness(inds[i],arr_length);
	}
}


int evolutionary_sorting(individual *inds[], int arr[],int ind_length , int arr_length) 
{
	int min1index=-1; 
	int min2index=-1;
	int least_fit_index;
	individual *new_child;
	populate_array(inds, arr, ind_length, arr_length);
	int c = 0;
	while (true)
	{	
		find_two_most_fit(inds, ind_length, &min1index, &min2index);
		least_fit_index = find_least_fit(inds, ind_length);
		new_child = make_child(inds[min1index], inds[min2index], arr_length);
		free(inds[least_fit_index]);	
		inds[least_fit_index] = new_child;
		c++;
		if (inds[find_most_fit(inds, ind_length)]->fitness == 0)
		{	
			printf("%d\n",c);
			return find_most_fit(inds, ind_length);
		}
		
	}
	//return find_most_fit(inds, ind_length);
}


int main() 
{
	srand(time(NULL));
	int arr[] = {34,23,6,11,8,40,37,36,77,51,12,33,1,457,88,22,30,98,65,48,26,2222,73,19,82,46,46,2,2,2};
	//this doesnt work when the array has duplicate elements because of the contains function inside makechild
	//this can be solved with declaring an array and marking all the elements taken from first and then inserting non marked elements 
	//marking is done with the value at index i = 0 or i=-1 insert if it is not 0 or -1
	//this is done now the array cant take -1 as a value 


	//an alternate child making could be probability based instead of finding the two most fit 
	//higher the fitness higher the odds which might make a more varied population which might lead to a faster solution
	//right now the solution is reached extremely slowly this might speed up the process

	//another method would be to get the fittest two and produce n-2 children and replace the n-2 least fit members 
	//which would create a more optimised generation and might lead to a faster solution


	individual *inds[10];
	int arr_length = sizeof(arr) / sizeof(arr[0]);
	for (size_t i = 0; i < 10; i++)
	{
		inds[i] = new_individual(arr_length);
	}

	int a=evolutionary_sorting(inds, arr, 10 , arr_length);
	print_array(inds[a]->arr,arr_length);
}