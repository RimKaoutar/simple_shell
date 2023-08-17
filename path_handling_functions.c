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

/**
 * get_command - gets the full path of a command
 * @command: the command to get the path of
 *
 * Return: the full path of the command, or NULL if it does not exist
 */
char *get_command(char *command)
{
	char *path = _getenv("PATH");
	char *token;
	char *full_cmd;
	struct stat st;

	token = strtok(path, ":");
	while (token)
	{
		full_cmd = malloc(strlen(token)) + strlen(command) + 2);
		strcpy(full_cmd, token);
		strcat(full_cmd, "/");
		strcat(full_cmd, command);
		if (stat(cmd, &st) == 0)
			return (full_cmd);
		free(full_cmd);
		token = strtok(NULL, ":");
	}
	return (NULL);
}
