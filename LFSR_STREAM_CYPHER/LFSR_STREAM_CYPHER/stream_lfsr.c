#include <stdio.h>
#include <stdint.h>
#include <time.h>

unsigned lfsr(void)
{
	uint32_t start_state = time(NULL);  
	uint32_t res = start_state;
	uint32_t period = 0;
	do
	{
		res ^= res >> 31;
		res ^= res << 29;
		res ^= res >> 1;
		++period;
	} while (res != start_state);
	return period;
}

void stream_cipher(uint32_t key, char x[], int length) 
{
	for (size_t i = 0; i < length; i++)
	{
		x[i] = key ^ x[i];
	}
}

int main() 
{
	uint32_t key= lfsr();
	char mesaj[] = "cok gizli mesaj";
	stream_cipher(key, mesaj, 16);
	printf("%s\n",mesaj);
	stream_cipher(key, mesaj, 16);
	printf("%s\n",mesaj);
}










