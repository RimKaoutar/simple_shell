#include "shell.h"

/**
 * checker - checks is the line_buffer has exit or env in it
 * @line_buffer: the line buffer
 * @envp: the environ pointer
 * Return: 1 for exit, 2 for env, 0 for a command that exists, -1 for
 * a command that doesn't exist
*/
int checker(char *line_buffer, char **envp)
{
	char *temp;
	if (_strcmp(_strtok(temp = _strdup(line_buffer), "\t\n "), "exit") == 0)
	{
		free(temp);
		return (1);
	}
	if (_strcmp(_strtok(temp = _strdup(line_buffer), "\t\n "), "env") == 0)
	{
		free(temp);
		print_env(envp);
		return (2);
	}
	return (0);
}
