#include <stdio.h>
#include <Windows.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 8
int board[SIZE][SIZE];

typedef enum bool{false, true}bool;

void printboard(int board[SIZE][SIZE])
{
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
		{
			printf("%d ",board[i][j]);
		}
		printf("\n");
	}
}



void zero_out(int board[][SIZE],int k)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
		{
			if (board[i][j] == k)
			{
				board[i][j] = 0;
			}
			
		}
	}
}

bool check(int arr[][SIZE], int x, int y, int p) 
{
	int qc = 8;
	int count = 0;
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
		{
			if (board[i][j] > 0)
			{
				count++;
			}

		}
	}
	if (qc==count)
	{
		
		
		//check vertical
		for (size_t i = 0; i < SIZE; i++)
		{
			if (arr[i][y] > 0 && arr[i][y] != p) 
			{
				return false;
			}
		}
		// Check horizontal.
		for (size_t i = 0; i < SIZE; i++)
		{
			if (arr[x][i] > 0 && arr[x][i] != p)
			{
				return false;
			}
		}

		// Check diagonal upper-left to lower-right.
		for (int i = 0; i < SIZE; i++)
		{
			if ((x + i + 1 < SIZE) && (y + i + 1 < SIZE))//&& arr[SIZE - i - 1][SIZE - i - 1] != p
			{
				if ((arr[x + i][y + i] > 0) && (arr[x + i][y + i] != p))
				{
						//printf("\n%d\n", arr[x + i][y + i]);
						return false;
				}
			}

			if ((x - i  >= 0) && (y - i  >= 0))//&& arr[SIZE - i - 1][SIZE - i - 1] != p
			{
				if ((arr[x - i][y - i] > 0) && (arr[x + i][y + i] != p))
				{
					return false;
				}
			}

		}

		// Check diagonal upper-right to lower-left.
		for (int i = 0; i < SIZE; i++)
		{
			if ((x - i - 1 > 0) && (y + i + 1 < SIZE))//&& arr[SIZE - i - 1][SIZE - i - 1] != p
			{
				if ((arr[x - i][y + i] > 0) && (arr[x + i][y + i] != p))
				{
					return false;
				}
			}

			if ((x + i + 1 < SIZE) && (y - i - 1 > 0))//&& arr[SIZE - i - 1][SIZE - i - 1] != p
			{
				if ((arr[x + i][y - i] > 0) && (arr[x + i][y + i] != p))
				{
					return false;
				}
			}

		}
		return true;

	}
	else
	{
		return false;
	}
	
}

int t = 0;


int brute_queens(int arr[][SIZE])
{
	for (size_t i = 0; i < SIZE*SIZE; i++)
	{
		//arr[(i / SIZE)][i%SIZE] = 8;
		for (size_t j = 0; j < SIZE*SIZE; j++)
		{
			//arr[(j / SIZE)][j%SIZE] = 7;
			for (size_t k = 0; k < SIZE*SIZE; k++)
			{
				//arr[(k / SIZE)][k%SIZE] = 6;
				for (size_t l = 0; l < SIZE*SIZE; l++)
				{
					//arr[(l / SIZE)][l%SIZE] = 5;
					for (size_t m = 0; m < SIZE*SIZE; m++)
					{
						//arr[(m / SIZE)][m%SIZE] = 4;
						for (size_t n = 0; n < SIZE*SIZE; n++)
						{
							//arr[(n / SIZE)][n%SIZE] = 3;
							for (size_t o = 0; o < SIZE*SIZE; o++)
							{
								//arr[(o / SIZE)][o%SIZE] = 2;
								for (size_t p = 0; p < SIZE*SIZE; p++)
								{
									
									arr[(i / SIZE)][i%SIZE] = 8;
									arr[(j / SIZE)][j%SIZE] = 7;
									arr[(k / SIZE)][k % SIZE] = 6;
									arr[(l / SIZE)][l % SIZE] = 5;
									arr[(m / SIZE)][m % SIZE] = 4;
									arr[(n / SIZE)][n % SIZE] = 3;
									arr[(o / SIZE)][o % SIZE] = 2;
									arr[(p / SIZE)][p % SIZE] = 1;

									if (check(board, (j / SIZE), j%SIZE, 7) 
										&& (check(board, (i / SIZE), i % SIZE, 8))
										&& (check(board, (k / SIZE), k % SIZE, 6))
										&& (check(board, (l / SIZE), l % SIZE, 5))
										&& (check(board, (m / SIZE), m % SIZE, 4))
										&& (check(board, (n / SIZE), n % SIZE, 3))
										&& (check(board, (o / SIZE), o % SIZE, 2))
										&& (check(board, (p / SIZE), p % SIZE, 1))
										)
									{
										return 1;	
									}

									zero_out(arr,1);
								}
								zero_out(arr,2);
							}
							zero_out(arr,3);
						}
						zero_out(arr,4);
					}
					zero_out(arr,5);
				}
				zero_out(arr,6);
			}
			zero_out(arr,7);
		}
		zero_out(arr,8);
	}
	
}


int test(int arr[][SIZE])
{
	for (size_t i = 0; i < SIZE*SIZE; i++)
	{
		
		//arr[(i / SIZE)][i%SIZE] = 2;
		for (size_t j = 0; j < SIZE*SIZE; j++)
		{
			arr[(i / SIZE)][i%SIZE] = 2;
			arr[(j / SIZE)][j%SIZE] = 1;
			//printboard(board);
			//printf("\n");
			if (check(board, (j / SIZE), j%SIZE, 1) && (check(board, (i / SIZE), i % SIZE, 2)))
			{
				printboard(board);
				printf("\n");
				if (t>3)
				{
					return 1;
				}
				else
				{
					t++;
				}
			}
			
			zero_out(arr,1);
		}
		zero_out(arr,2);
	}
	return 0;
}



int main()
{
	

	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
		{
			board[i][j] = 0;
		}
	}
	
	brute_queens(board);
	

	//printboard(board);

}