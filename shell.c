#include "shell.h"
/**
 * is_interactive - checks the interactivity, still needs work!!
 * @ac: the num of args
 * Return: if there is no args executes with the program, return 0
*/
int is_interactive(int ac)
{
	return ((ac > 1) ? 1 : 0);
}
/**
 * main - execute hsh
 * @ac: the num of args
 * @av: the args
 * Return: 0 as exit_success
*/
int main(int ac, char *av[])
{
	getline_return *gr = malloc(sizeof(getline_return));	
	pid_t pid;
	int stat;
	char **array;
	if (is_interactive(ac) == 0)
	{
		while(1)
		{
			gr = putline(gr);
			array = get_args(gr->line_buff);
			if (!*array)
				continue;
			pid = fork();
			if (pid == 0)
			{
				execve(array[0], array, NULL);
				perror(av[0]);
			}
			else
			{
				wait(&stat);
			}
			free(array);
		}
	}
	return (0);
}
