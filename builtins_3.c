#include "shell.h"

/**
 * handle_builtin - Handles built-in shell commands
 * @info: Info struct containing command details
 *
 * Description:
 * Loops through struct of built-in commands
 * Compares argv[0] to command name
 * If match, calls corresponding function
 *
 * Return: value from built-in function or -1
 */
int handle_builtin(shell_t *info)
{
	int i = 0;
	int ret_vlr = -1;

	builtin_commands buits[] = {
		{"cd", handle_cd},
		{"env", _printenv},
		{"exit", handle_exit},
		{"help", handle_help},
		{"alias", handle_alias},
		{"setenv", check_setenv},
		{"history", handle_history},
		{"unsetenv", check_unsetenv},
		{NULL, NULL}};

	for (; buits[i].type; i++)
		if (_strcmp(info->argv[0], buits[i].type) == 0)
		{
			info->lines++;
			ret_vlr = buits[i].func(info);
			break;
		}
	return (ret_vlr);
}