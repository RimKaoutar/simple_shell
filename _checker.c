#include "shell.h"

/**
 * checker - checks line buffer for builtin commands
 * @line_buffer: the command line
 * @envp: environ pointer
 * Return: command indicator or 0 if not found
 */
int checker(char *line_buffer, char **envp) {

	char *token = _strtok(line_buffer, " \t\n");

	if(_strcmp(token, "exit") == 0) {
		return 1;
	}

	if(_strcmp(token, "env") == 0) {
		print_env(envp);
		return 2;
	}

	if(_strcmp(token, "setenv") == 0) { 
		
		_setenv(token, _strtok(NULL, " \t\n"), (_strcmp(_strtok(NULL, " \t\n"), "1"))? false : true);
		return 3;
	}

	if(_strcmp(token, "unsetenv") == 0) {
		_unsetenv(_strtok(NULL, " \t\n"));
		return 4;
	}
	return 0;
}
