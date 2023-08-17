#include "shell.h"

/**
 * _getenv - gets the value of an environment variable
 * @env_var: the name of the environment variable
 *
 * Return: the value of the environment variable, or NULL if it does not exist
 */
char *_getenv(const char *env_var)
{
	extern char **environ;
	int i = 0;
	char *token;

	while (environ[i])
	{
		token = strtok(environ[i], "=");
		if (strcmp(token, env_var) == 0)
		{
			return (strtok(NULL, "\n"));
		}
		i++;
	}
	return (NULL);
}
