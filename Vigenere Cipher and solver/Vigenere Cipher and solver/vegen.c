#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <ctype.h>

char *encyrypt(char *arr, char *key)
{
	char *encrypted_text = malloc(strlen(arr) * sizeof(char));

	for (size_t i = 0; i < strlen(arr); i++)
	{
		
		int c = arr[i] - 65;
		int k = key[i%strlen(key)] - 65;
		
		encrypted_text[i] = ((c + k) % 26) + 65;

	}
	encrypted_text[strlen(arr)] = '\0';
	return encrypted_text;
}


char *decrypt(char *arr, char *key)
{
	char *res= malloc(strlen(arr) * sizeof(char));
	int keymod = strlen(key);

	for (size_t i = 0; i < strlen(arr); i++)
	{

		int e = arr[i] - 65;
		int k = key[i%keymod] - 65;
		int d = ((e - k + 26) % 26);

		res[i] = d + 65;


	}
	res[strlen(arr)] = '\0';
	return res;
}


char *turn_upper_case_and_remove_spaces(char *arr)
{
	int j = 0;
	char *res = malloc(strlen(arr) * sizeof(char));
	//res[strlen(arr)] = '\0';

	int len = strlen(arr);
	int spaces = 0;

	for (size_t i = 0; i < len; i++)
	{
		if (arr[i]>96 && arr[i]<123)
		{
			res[j] = arr[i] - 32;
			j++;
		}
		else if (arr[i] == ' ')
		{
			spaces++;
		}
		else
		{
			res[j] = arr[i];
			j++;
		}
		
	}
	res[(len-spaces)]='\0';
	return res;
}



size_t shifting(char *arr, int shifting_coefficent)
{
	int len = strlen(arr);
	size_t hit = 0;
	for (size_t i = 0; i < len; i++)
	{
		if (i+shifting_coefficent>len)
		{
			break;
		}
		if (arr[i] == arr[i + shifting_coefficent])
		{
			hit++;
		}
	}
	return hit;
}




int main()
{

	double frequency[] = {0.082, 0.15, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002, 0.008, 0.040, 0.024,
		0.064, 0.075, 0.019, 0.001, 0.060, 0.063, 0.091, 0.028, 0.010, 0.023, 0.001, 0.020, 0.001};

	double frreq2[] = { 0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 
		0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074 };

	char *arr = "HELLOWORLD";
	arr = turn_upper_case_and_remove_spaces(arr);
	char *res;
	char *key = "QW";
	//printf("sdjhfjhkgjkhgjkhgjhgkhkjjkhgkhgjkhghs");
	
	
	printf("%s\n", arr);
	res = encyrypt(arr, key);
	
	printf("%s\n", res);


	size_t hits = shifting(res,4);
	printf("%d\n",hits);


	res = decrypt(res, key);

	printf("%s\n", res);


	return 0;
}
