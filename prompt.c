#include "minishell.h" 

int main(int ac, char **argv, char **envp)
{
	char *res;
	while (1)
	{	
		char prompt[] = "\x1b[35muser prompt>> \x1b[0m";
		res = readline(prompt);
		tokenize(prompt);
		printf("we had %s \n", res);
	}
}