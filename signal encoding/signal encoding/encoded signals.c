#include <stdio.h>


void NRZ_L(char *str)
{
	for (int i=0; str[i] != '\0'; i++)
	{
		if (str[i]=='0')
		{
			printf("H");
		}
		else
		{
			printf("L");
		}
		printf("|");
	}
}


void NRZI(char *str)
{	
	int state = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		
		if (str[i]=='1')
		{
			state ^= 1;//not operation using xor
		}
		if (state)
		{
			printf("H");
		}
		else
		{
			printf("L");
		}
		printf("|");
	}
}


void Bipolar_AMI(char *str)
{
	int state = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '0')
		{
			printf("M");
		}
		else
		{
			if (str[i] == '1')
			{
				state ^= 1;//not operation using xor
			}
			if (state)
			{
				printf("H");
			}
			else
			{
				printf("L");
			}
		}
		printf("|");
	}
}


void Pseudoternary(char *str)
{
	int state = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '1')
		{
			printf("M");
		}
		else
		{
			if (str[i] == '0')
			{
				state ^= 1;//not operation using xor
			}
			if (state)
			{
				printf("H");
			}
			else
			{
				printf("L");
			}
		}
		printf("|");
	}
}


void Manchester(char *str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '0')
		{
			printf("HL");
		}
		else
		{
			printf("LH");
		}
		printf("|");
	}
}


void Diff_Manchester(char *str)
{
	int state = 1;
	for (int i = 0; str[i] != '\0'; i++)
	{
		
		if (str[i] == '0')
		{
			
			if (state)
			{
				printf("LH");
			}
			else
			{
				printf("HL");
			}
		}
		else
		{
			state ^= 1;//not operation using xor

			if (state)
			{
				printf("LH");
			}
			else
			{
				printf("HL");
			}
			
		}
		printf("|");
	}
}


int main()
{
	char str[] = "010011000111010001111110";
	printf("%s=     ", str);


	//NRZ_L(str);
	//NRZI(str);
	//Bipolar_AMI(str);
	//Pseudoternary(str);
	Manchester(str);
	//Diff_Manchester(str);
}