#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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



int find_keylength(char *res,int shifting_amount)
{
	int keylen = 0;
	int prev = 0;

	int hits =  0 ;
	for (int i = 1; i < shifting_amount; i++)
	{
		hits = shifting(res, i);

		if (hits > prev)
		{
			keylen = i;
			prev = hits;
		}

	}
	return keylen;
}


void shift_array_by_one(double *arr,int len)
{
	
	len--;

	double tmp = arr[len];

	for (int i = len-1; i >= 0; i--)
	{
		arr[i+1] = arr[i];
	}
	arr[0] = tmp;
}




double scaler_mult(double *arr1, double *arr2, int len)
{
	double res = 0;

	for (size_t i = 0; i < len; i++)
	{
		res += arr1[i] * arr2[i];
	}

	return res;
}





char* findkey(char *arr,int keylen, char *frreq2)
{
	char *res = malloc(keylen*sizeof(char));
	res[keylen] = '\0';
	for (size_t a = 0; a < keylen; a++)
	{


		printf("%d\n", keylen);

		int freq_mod = strlen(arr) / keylen;

		double letters[26] = { 0 };
		for (size_t k = a; k < strlen(arr); k += keylen)
		{
			int letter = res[k] - 65;
			letters[letter]++;
		}

		for (size_t i = 0; i < 26; i++)
		{
			letters[i] = letters[i] / (double)freq_mod;
		}
		//letters is w frreq2 a0

		double largest = 0;
		int index = 0;
		for (size_t i = 0; i < 26; i++)
		{
			double res = scaler_mult(letters, frreq2, 26);

			if (res > largest)
			{
				largest = res;
				index = i;
			}
			shift_array_by_one(frreq2, 26);
		}

		res[a]= (index + 65);
		printf("%c\n", index + 65);



	}


	return res;
}



int main()
{

	double frequency[] = {0.082, 0.15, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002, 0.008, 0.040, 0.024,
		0.064, 0.075, 0.019, 0.001, 0.060, 0.063, 0.091, 0.028, 0.010, 0.023, 0.001, 0.020, 0.001};

	double frreq2[] = { 0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 
		0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074 };

	char *arr = "hello is this thing working";
	arr = turn_upper_case_and_remove_spaces(arr);
	char *res;
	char *key = "qw";
	key = turn_upper_case_and_remove_spaces(key);
	printf("%s\n", arr);
	res = encyrypt(arr, key);	
	printf("%s\n", res);


	//int keylen = find_keylength(res, 20);

	//printf("%d\n",keylen);

	//char *cracked_key = findkey(res,keylen,frreq2);
	//printf("%s\n",cracked_key);


	res = decrypt(res, key);
	printf("%s\n", res);
	return 0;
}
