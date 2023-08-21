#include "shell.h"
/**
 * exec_non_interactive - executes in non interactive mode
 * @envp: the env pointer
*/
void exec_non_interactive(char **envp)
{
	char *line_buffer = NULL, *token, *saveptr, *args[] = {NULL};
	size_t n = 0;
	ssize_t chars_nbr;
	pid_t son;

	chars_nbr = non_interactive_getline(&line_buffer, &n, stdin);
	if (chars_nbr == -1)
	{
		perror("error:");
		free(line_buffer);
		exit(EXIT_FAILURE);
	}
	token = _strtok_r(line_buffer, " \n", &saveptr);
	
	while (token)
	{
		son = fork();
		if (son == -1)
		{
			perror("fork");
			free(line_buffer);
			exit(EXIT_FAILURE);
		}
		if (son == 0)
		{
			execve(token, args, envp);
			perror("execve");
		}
		else
			wait(NULL);
		token = _strtok_r(NULL, " \n", &saveptr);
	}
	free(line_buffer);
	exit(EXIT_SUCCESS);
}