#include "shell.h"

/**
 * checker - checks line buffer for builtin commands
 * @line_buffer: the command line
 * @envp: environ pointer
 * Return: command indicator or 0 if not found
 */
int checker(char *line_buffer, char **envp) {

	char *cmd_copy = strdup(line_buffer);
	char *token = _strtok(cmd_copy, " \t\n");
	char *arg1, *arg2, *arg3;

	if(_strcmp(token, "exit") == 0)
	{
		free(cmd_copy);
		return 1;
	}
	if(_strcmp(token, "env") == 0)
	{
		print_env(envp);
		free(cmd_copy);
		return 2;
	}
	if(_strcmp(token, "setenv") == 0)
	{ 
		arg1 = _strtok(NULL, " \t\n");
		arg2 = _strtok(NULL, " \t\n");
		arg3 = _strtok(NULL, " \t\n");
		if(!arg1 || !arg2 )
		{
			perror("error");
			return (-1);
		}
		_setenv(arg1, arg2, (_strcmp(arg3, "1"))? false : true);
		free(cmd_copy);
		return (3);
	}

	if(_strcmp(token, "unsetenv") == 0)
	{
		arg1 = _strtok(NULL, " \t\n");
		_unsetenv(arg1);
		free(cmd_copy);
		return 4;
	}
	return 0;
}
