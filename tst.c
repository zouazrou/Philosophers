#include <unistd.h>
#include <stdio.h>

int main()
{
	long long x =  4294967200;
	printf("%ld\n", x / 1000);
	if (!usleep(-12))
		printf("usleep done\n");
	else
		printf("usleep failed\n");
	return 0;
}
