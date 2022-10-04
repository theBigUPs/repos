#include <stdio.h>
#include <string.h>

int gcd(int x, int y)
{
	if (y != 0) 
	{
		return gcd(y, x % y);
	}
	else 
	{
		return x;
	}
}

int encrypt(char str[], int a, int b, int m) 
{
	//char crypted[500];
	if(gcd(a,m)!=1)
	{ 
		printf("a ve m aralarinda asal degil");
		return -1;
	}

	for (size_t i = 0; i < strlen(str); i++)
	{
		if ((str[i] >= 65) && (str[i] <= 90))
		{
			int crypting = (a*(str[i] - 65) + b) % m;
			str[i] = crypting + 65;
		}
		
	}
	printf("%s\n",str);
	return 1;
	//return dec;
}

void decrypt(char str[], int a, int b, int m)
{

	int inverse_a = 0;
	for (size_t i = 1; i < m; i++) // modulusun tersini bulma
	{
		if ((a*i) % m == 1)
		{
			inverse_a = i;
		}
	}

	for (size_t i = 0; i < strlen(str); i++)
	{
		if ((str[i] >= 65) && (str[i] <= 90))
		{
			int decrypting = (inverse_a*((str[i] - 65) - b)) % m;
			if (decrypting < 0)
			{
				decrypting = 26 + (decrypting);
			}
			str[i] = decrypting + 65;
		}
	}
	printf("%s\n", str);
}

int main()//sadece buyuk harfler ile calisir
{
	char txt[]="GIZLI MESAJ";
	int a = 17;
	int b = 20;
	int m = 26;
	encrypt(txt,a,b,m);
	decrypt(txt, a, b, m);
	//printf("%d\n",gcd(a,26));
}