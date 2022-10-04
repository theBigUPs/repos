#include <stdio.h>
#include <stdlib.h>
//Microsoft Visual / Quick C / C++:	modulus m = 2^32 = 4294967296,	multipilier a=214013 ,	 increment b=2531011 
// hocam kendi lcg mi yazdim stanadart kutupanenin lcg sinde calismiyodu formul

long long rseed = 0;
void lcg_seed(long long seed) 
{
	rseed = seed;
}


long long lcg()
{
	long long a = 214013;
	long long b = 2531011;
	long long modulus = 4294967296;
	rseed = (rseed*a + b) % modulus;
	return rseed;
}

long long modular_inverse(long long a, long long m) 
{
	
		for (long long x = 1; x < m; x++)
			if (((a%m) * (x%m)) % m == 1)
				return x;
	
		return 1;
}

void solve_lcr(long long s1, long long s2, long long s3)
{
	long long m = 4294967296;
	long long a1 = s2 - s3;
	long long a2b3 = s1 - s2;
	if (a1<0)
	{
		a1 = a1+m;
	}
	if (a2b3 < 0)
	{
		a2b3 = a2b3 + m;
	}

	long long a= (a1) * modular_inverse((a2b3),m) % m;
	long long b = (s2 - s1 * (a1) *modular_inverse((a2b3),m)) % m;
	//long long b = (s2 - a * s1)%m;
	if (b<0)
	{
		b += m;
	}

	printf("a= %lu ", a);
	printf("b= %lu \n",b);
}

int main()
{
	int s0 = 123;
	lcg_seed(s0);
	long long s1 = lcg();
	printf("s1= %lu", s1);
	long long s2 = lcg();
	printf(" s2= %lu", s2);
	long long s3 = lcg();
	printf(" s3= %lu\n\n", s3);
	solve_lcr(s1, s2, s3);
}