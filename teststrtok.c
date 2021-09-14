#include <string.h>
#include <stdio.h>

int main(int ac, char **argv)
{	

	int i = 0;
	char *res = strtok(argv[1], " ");
	//while (res[i])
	while (res)
	{
	
		printf("token :: %s\n", res);
		res = strtok ( NULL, " " );
	}
}