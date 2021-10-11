#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>



#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd;
	char buf[20];

	fd = open("inexistantfile", O_RDONLY);
	int errno1 = errno;
	//printf ("%s \n", strerror(errno));

	if(read(fd, buf, 1)==-1)
		printf ("%s \n", strerror(errno));
	printf ("first pb was %s \n", strerror(errno1));

}
