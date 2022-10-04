#include <stdio.h>
#include <string.h>
//take 4 bytes 
//take the next 4 xor with first
//continue until finished
//if the message cant be divided into 4 byte chunks add padding bits at the end 
char *xor_hash(char message[])
{
	int len = strlen(message);
	if (len%4!=0)
	{
		for (size_t i = 0; i < 4-(len%4); i++)
		{
			message[len + i] = 'a'; //padding
		}
	}
	len = strlen(message);
	int xor = message[0] + message[1] + message[2] + message[3];
	message[0] = message[0] ^ xor;
	message[1] = message[1] ^ xor;
	message[2] = message[2] ^ xor;
	message[3] = message[3] ^ xor;
	for (size_t i = 4; i < len; i++)
	{
		int xor = message[i-1] + message[i-2] + message[i-3] + message[i-4];
		message[i] = message[i] ^ xor;
	}

	return message;
}

int main()
{
	char message[500] = "hello world";
	printf("%s\n",xor_hash(message));
}