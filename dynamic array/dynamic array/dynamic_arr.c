#include <stdio.h>
#include <stdlib.h>

/* dynamic array */
// 1,2,3,4,5,6...

//access: O(1)
//add:    O(n)
//remove: O(1)
//find:   O(n)
//find min: O(n)
//find max: O(n)

typedef struct dynamic_array
{

	int* data;
	int size;

}vec;

int miny(vec* a)
{
	int m = a->data[0];

	for (int i = 1; i < a->size; i++)
	{
		if (a->data[i] < m)
			m = a->data[i];
	}

	return m;
}


int maxy(vec* a)
{
	int m = a->data[0];

	for (int i = 1; i < a->size; i++)
	{
		if (a->data[i] > m)
			m = a->data[i];
	}

	return m;
}

int find(vec* a, int what)
{
	for (int i = 0; i < a->size; i++)
	{
		if (a->data[i] == what)
			return i;
	}

	return -1;
}

int get(vec* a, int idx)
{
	return a->data[idx];
}

// vector
int write(vec* a, int what, int idx)
{
	if (idx > a->size)
	{
		int* tmp = malloc(sizeof(int)*(2 * idx));
		for (int i = 0; i < a->size; i++)
		{
			tmp[i] = a->data[i];
		}
		free(a->data);
		a->data = tmp;
	}

	a->data[idx] = what;
	return 0;
}

vec allocate(int howmany)
{
	vec da;
	da.data = malloc(sizeof(int)*howmany);
	da.size = howmany;

	return da;
}

int main()
{
	vec da = allocate(10);
	write(&da, 10, 0);
	write(&da, 20, 1);
	write(&da, 30, 2);

	//if (find(&da, 10) != -1)
	{
		//printf("We have 10 in this dynamic array");
	}
	printf("%d\n\n\n",da.data[2]);
	return 0;
}