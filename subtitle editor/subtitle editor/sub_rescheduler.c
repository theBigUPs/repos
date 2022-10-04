#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
typedef enum {false ,true }bool;


int chartoint(char c)
{
	switch (c)
	{
	case '1': return 1; break;
	case '2': return 2; break;
	case '3': return 3; break;
	case '4': return 4; break;
	case '5': return 5; break;
	case '6': return 6; break;
	case '7': return 7; break;
	case '8': return 8; break;
	case '9': return 9; break;
	case '0': return 0; break;
	default: return -1;
		break;
	}
}

char inttochar(int i )
{
	switch (i)
	{
	case 1: return '1'; break;
	case 2: return '2'; break;
	case 3: return '3'; break;
	case 4: return '4'; break;
	case 5: return '5'; break;
	case 6: return '6'; break;
	case 7: return '7'; break;
	case 8: return '8'; break;
	case 9: return '9'; break;
	case 0: return '0'; break;
	default: return -1;
		break;
	}
}

void add(FILE *subs, int sec, int min, int hour)
{
	sec += min * 60 + hour * 3600;
	int secoriginal = sec;
	int counter = 0;
	char buffer[500];
	int coloncounter = 0;
	int mult = 1;
	char test[500];
	FILE *fin;
	fin = fopen("fin.txt", "w");

	
	
	while (fgets(buffer, 500, subs) != NULL)
	{
		++counter;

		if ((counter % 2 == 0) && (counter % 4 != 0))
		{
			strcpy(test, buffer);


			for (int i = 7; i >= 0; i--)
			{
				if (test[i] == ':')
				{
					coloncounter++;
					mult = 1;
				}
				if (coloncounter == 0)
				{
					sec += chartoint(test[i])*mult;

					mult *= 10;
				}
				if (coloncounter == 1 && test[i] != ':')
				{
					sec += chartoint(test[i]) * 60 * mult;
					mult *= 10;
				}
				if (coloncounter == 2 && test[i] != ':')
				{
					sec += chartoint(test[i]) * 3600 * mult;
					mult *= 10;
				}
			}

			int newhour = sec / 3600;
			int newmin = (sec % 3600) / 60;
			int newsec = (sec % 3600) % 60;


			test[7] = inttochar(newsec % 10);
			test[6] = inttochar(newsec / 10);
			test[4] = inttochar(newmin % 10);
			test[3] = inttochar(newmin / 10);
			test[1] = inttochar(newhour % 10);
			test[0] = inttochar(newhour / 10);

			coloncounter = 0;
			sec = secoriginal;
			mult = 1;




			for (int i = 24; i >= 17; i--)
			{
				if (test[i] == ':')
				{
					coloncounter++;
					mult = 1;
				}
				if (coloncounter == 0)
				{
					sec += chartoint(test[i])*mult;

					mult *= 10;
				}
				if (coloncounter == 1 && test[i] != ':')
				{
					sec += chartoint(test[i]) * 60 * mult;
					mult *= 10;
				}
				if (coloncounter == 2 && test[i] != ':')
				{
					sec += chartoint(test[i]) * 3600 * mult;
					mult *= 10;
				}
			}

			newhour = sec / 3600;
			newmin = (sec % 3600) / 60;
			newsec = (sec % 3600) % 60;


			test[24] = inttochar(newsec % 10);
			test[23] = inttochar(newsec / 10);
			test[21] = inttochar(newmin % 10);
			test[20] = inttochar(newmin / 10);
			test[18] = inttochar(newhour % 10);
			test[17] = inttochar(newhour / 10);
			coloncounter = 0;
			sec = secoriginal;
			mult = 1;


			fprintf(fin,"%s", test);

		}
		else
		{
			fprintf(fin, "%s", buffer);
		}


	}

	fclose(fin);

}

void subtract(FILE *subs, int sec, int min, int hour)
{
	sec += min * 60 + hour * 3600;
	int secoriginal = sec;
	int counter = 0;
	char buffer[500];
	int coloncounter = 0;
	int tobesubtracted = 0;
	int mult = 1;
	char test[500];
	FILE *fin;
	fin = fopen("fin.txt","w");


	while (fgets(buffer, 500, subs) != NULL)
	{
		++counter;

		if ((counter % 2 == 0) && (counter % 4 != 0))
		{
			//printf("%s", buffer);






			strcpy(test, buffer);



			for (int i = 7; i >= 0; i--)
			{
				if (test[i] == ':')
				{
					coloncounter++;
					mult = 1;
				}
				if (coloncounter == 0)
				{
					tobesubtracted += chartoint(test[i])*mult;

					mult *= 10;
				}
				if (coloncounter == 1 && test[i] != ':')
				{
					tobesubtracted += chartoint(test[i]) * 60 * mult;
					mult *= 10;
				}
				if (coloncounter == 2 && test[i] != ':')
				{
					tobesubtracted += chartoint(test[i]) * 3600 * mult;
					mult *= 10;
				}
			}

			if ((tobesubtracted - sec) < 0)
			{
				tobesubtracted = 0;
			}
			else
			{
				tobesubtracted -= sec;
			}



			int newhour = tobesubtracted / 3600;
			int newmin = (tobesubtracted % 3600) / 60;
			int newsec = (tobesubtracted % 3600) % 60;


			test[7] = inttochar(newsec % 10);
			test[6] = inttochar(newsec / 10);
			test[4] = inttochar(newmin % 10);
			test[3] = inttochar(newmin / 10);
			test[1] = inttochar(newhour % 10);
			test[0] = inttochar(newhour / 10);

			coloncounter = 0;
			sec = secoriginal;
			mult = 1;
			tobesubtracted = 0;


			for (int i = 24; i >= 17; i--)
			{
				if (test[i] == ':')
				{
					coloncounter++;
					mult = 1;
				}
				if (coloncounter == 0)
				{
					tobesubtracted += chartoint(test[i])*mult;

					mult *= 10;
				}
				if (coloncounter == 1 && test[i] != ':')
				{
					tobesubtracted += chartoint(test[i]) * 60 * mult;
					mult *= 10;
				}
				if (coloncounter == 2 && test[i] != ':')
				{
					tobesubtracted += chartoint(test[i]) * 3600 * mult;
					mult *= 10;
				}
			}



			if ((tobesubtracted - sec) < 0)
			{
				tobesubtracted = 0;
			}
			else
			{
				tobesubtracted -= sec;
			}


			newhour = tobesubtracted / 3600;
			newmin = (tobesubtracted % 3600) / 60;
			newsec = (tobesubtracted % 3600) % 60;


			test[24] = inttochar(newsec % 10);
			test[23] = inttochar(newsec / 10);
			test[21] = inttochar(newmin % 10);
			test[20] = inttochar(newmin / 10);
			test[18] = inttochar(newhour % 10);
			test[17] = inttochar(newhour / 10);


			coloncounter = 0;
			sec = secoriginal;
			mult = 1;
			tobesubtracted = 0;

			fprintf(fin, "%s", test);




		}

		else
		{
			fprintf(fin,"%s",buffer);
		}
	}





	fclose(fin);

}



int main()
{
	
	FILE *subs;
	subs = fopen("test.txt","r");

	
	add(subs,10,0,0);
	
	fclose(subs);
	
}