#include <sys/wait.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int status;

    pid_t pid;
    char blabla[2][10] = {
        [0] = "iqjfe",
        [1] = "fslkhfj"

    };
    
    pid = fork();
    if (pid == 0)
    {
        if (execvp("daljf", (char * const*)blabla) == -1)
					{
						perror("> exec error");
						exit (156);	
					}
        exit(127);
    }
    waitpid(pid, &status, 0);
    printf ("stat %d \n", WEXITSTATUS(status));
}