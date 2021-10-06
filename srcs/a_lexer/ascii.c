#include <stdio.h>

int main(void)
{
	int i = 0;
	while (i <= 256)
	{
		printf ("%d : %c \n", i, i);
		i++;
	}
	return (0);
}