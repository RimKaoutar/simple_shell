#include "shell.h"

/**
 * checker - checks line buffer for builtin commands
 * @line_buffer: the command line
 * @envp: environ pointer
 * Return: command indicator or 0 if not found
 */
int checker(char *line_buffer, char **envp) {

	/*debug line */
                                printf("in checker1 %s\n", line_buffer);
	char *token = _strtok(line_buffer, " \t\n");
	char *arg1, *arg2, *arg3;

	/*debug line */
                                printf("in checker1 %s\n", line_buffer);

	if(_strcmp(token, "exit") == 0) {
		return 1;
	}

	if(_strcmp(token, "env") == 0) {
		print_env(envp);
		return 2;
	}

	if(_strcmp(token, "setenv") == 0) { 
		arg1 = _strtok(NULL, " \t\n");
		arg2 = _strtok(NULL, " \t\n");
		arg3 = _strtok(NULL, " \t\n");
		if(!arg1 || !arg2 ) {
			fprintf(stderr, "Missing args\n");
			return -1;
		}
		_setenv(arg1, arg2, (_strcmp(arg3, "1"))? false : true);
		return 3;
	}

	if(_strcmp(token, "unsetenv") == 0) {
		arg1 = _strtok(NULL, " \t\n");
		_unsetenv(arg1);
		return 4;
	}
	/*debug line */
                                printf("inchecker1 %s\n", line_buffer);

	return 0;
}
