#include "shell.h"

/**
 * _getenv - gets the value of an environment variable
 * @env_var: the name of the environment variable
 *
 * Return: the value of the environment variable, or NULL if it does not exist
 */
char *_getenv(const char *env_var, char **envp)
{
	int i = 0;
	char *token;

	while (envp[i])
	{
		token = _strtok(envp[i], "=");
		if (strcmp(token, env_var) == 0)
		{
			return (_strtok(NULL, "\n"));
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
char *get_command(char *command, char **envp)
{
	char *path = _getenv("PATH", envp);
	char *token;
	char *full_cmd;
	struct stat st;

	token = _strtok(path, ":");
	while (token)
	{
		full_cmd = malloc(sizeof(char) * (_strlen(token) + _strlen(command) + 2));
		_strcpy(full_cmd, token);
		_strcat(full_cmd, "/");
		_strcat(full_cmd, command);
		if (stat(full_cmd, &st) == 0)
			return (full_cmd);
		token = _strtok(NULL, ":");
	}
	free(full_cmd);
	return (NULL);
}

/**
 * print_env - prints the environ of the current program
 * @envp: the environ pointer
*/

void print_env(char **envp)
{
	int i = 0;

	while (envp[i])
	{
		write(1,envp[i], _strlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
}
