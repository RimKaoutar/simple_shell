#include "shell.h"

/**
 * splitstr - Split a string into tokens
 * @str: The string to be split
 *
 * Return: An array of tokens
 */
char **splitstr(char *str)
{
	char *token, **tokens = NULL;
	int count = 0;

	token = strtok(str, " \t\n");
	while (token)
	{
		tokens = _realloc(tokens,count * sizeof(char *),(count + 1) * sizeof(char *));
		count++;
		if (!tokens)
		{
			perror("realloc couldn't alloc :(");
			exit(EXIT_FAILURE);
		}
		tokens[count - 1] = token;
		token = strtok(NULL, " \t\n");
	}
	tokens[count] = NULL;
	return (tokens);
}

