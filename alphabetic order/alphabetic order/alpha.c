#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#pragma warning(disable:4996)
#define BUFFER 1024



int line_count(FILE *fp)//this works but very inefficiently this could be said for the entirety of this code
{
	int ln = 0;
	char c;
	for (c = getc(fp); c != EOF; c = getc(fp))
	{
		if (c == '\n')
		{
			ln = ln + 1;
		}
	}
	fseek(fp, 0, SEEK_SET);
	return ln;
}


int main()
{
	FILE *f;
	f = fopen("ordernt.txt", "r");
	int ln = line_count(f)+1;

	char **str_arr;
	char temp[BUFFER];



	str_arr = malloc(ln * sizeof(char*));//dynamic string array
	for (int i = 0; i < ln; i++)
	{
		str_arr[i] = malloc((BUFFER) * sizeof(char));
	}
	int first = 0;
	int second = 0;



	for (size_t i = 0; fgets(str_arr[i], BUFFER-1, f); i++);//gets the lines from file and sets the lines to the array



	int a = strlen(str_arr[ln-1]);//if the last line doesnt have a \n at the end of it this code adds a \n to it
	int line = 1;
	if (a > BUFFER)
	{
		a = strlen(str_arr[ln - 2]);
		line = 2;
	}
	if (str_arr[ln - line][a-1] != '\n')
	{
		str_arr[ln - line][a] = '\n';
		str_arr[ln - line][a + 1] = '\0';
	}



	int charindex = 0;
	for (; ; charindex++)//the main logic this is where the sorting is done
	{
		size_t j = 0;
		size_t i = 0;
		for (; i < ln - (line-1) ; i++)
		{
			size_t j = 0;
			for (; j < ln - i - line; j++)
			{
				if ((str_arr[j][charindex] == '\n') || (str_arr[j][charindex] == '\0'))
				{
					break;
				}
				first = tolower(str_arr[j][charindex]);
				second = tolower(str_arr[j + 1][charindex]);
				if ((first > second) && (charindex == 0))
				{
					strcpy(temp, str_arr[j]);
					strcpy(str_arr[j], str_arr[j + 1]);
					strcpy(str_arr[j + 1], temp);
				}
				else if ((first > second) && (charindex != 0) )
				{
					int res = 0;
					for (size_t k = 0; k < charindex; k++)
					{
						if (tolower(str_arr[j][k]) == tolower(str_arr[j + 1][k]))
						{
							res = 1;
						}
						else
						{
							res = 0;
							break;
						}
					}
					if (res==1)
					{
						strcpy(temp, str_arr[j]);
						strcpy(str_arr[j], str_arr[j + 1]);
						strcpy(str_arr[j + 1], temp);
					}
					

				}
			}
		}
		if ((str_arr[j][charindex] == '\n') || (str_arr[j][charindex] == '\0'))
		{
			break;
		}
		
	}


	FILE *fw;
	fw = fopen("done.txt", "w");

	for (size_t i = 0; i < ln- (line - 1); i++)
	{
		fputs(str_arr[i], fw);
	}
	
	
	fclose(f);
	fclose(fw);
	free(str_arr);
}