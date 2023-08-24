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

/**
 * create_process - Forks a new process and executes a command
 * @informati: Info struct containing command details
 *
 * Description:
 * Forks using fork() to create a child process
 * Child process tries to execve() the command
 * Parent waits for child and stores exit status
 * Handles errors from execve() and permission denied
 *
 * Returns: Nothing
 */

void create_process(shell_t *informati)
{
	pid_t son = fork();

	if (son == -1)
	{
		perror("Error:");
		return;
	}
	if (son == 0)
	{
		if (execve(informati->path, informati->argv, get_environ(informati)) == -1)
		{
			free_info(informati, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(informati->status));
		if (WIFEXITED(informati->status))
		{
			informati->status = WEXITSTATUS(informati->status);
			if (informati->status == 126)
				print_error(informati, "Permission denied\n");
		}
	}
}

/**
 * shell_main - Main loop for the shell interpreter
 * @informations: Info struct
 * @av: Argument vector
 *
 * Description:
 * Loops getting input and processing commands
 * Handles builtins or calls command checker
 * Cleans up after each loop iteration
 * Exits with appropriate status on error or quit
 *
 * Return: exit status or -2 if quit
 */
int shell_main(shell_t *informations, char **av)
{
	ssize_t rd_res = 0;
	int btin_rtrn_vl = 0;

	while (rd_res != -1 && btin_rtrn_vl != -2)
	{
		clear_info(informations);
		if (from_terminal(informations))
			_puts("$ ");
		putchar_err(NEG_ONE);
		rd_res = get_input(informations);
		if (rd_res != -1)
		{
			set_info(informations, av);
			btin_rtrn_vl = handle_builtin(informations);
			if (btin_rtrn_vl == -1)
				check_command(informations);
		}
		else if (from_terminal(informations))
			_putchar('\n');

		free_info(informations, 0);
	}
	create_history(informations);
	free_info(informations, 1);
	if (!from_terminal(informations) && informations->status)
		exit(informations->status);
	if (btin_rtrn_vl == -2)
	{
		if (informations->error_code == -1)
			exit(informations->status);
		exit(informations->error_code);
	}
	return (btin_rtrn_vl);
}

/**
 * check_command - Checks and executes a non-builtin command
 * @informationes: Info struct containing command details
 *
 * Description:
 * Checks if command is executable using PATH search
 * Sets command path and calls process creator
 * Prints error if command not found
 * Handles case of empty command and built-ins returning
 *
 * Return: Nothing.
 */
void check_command(shell_t *informationes)
{
	char *pathh = NULL;
	int i;
	int words_nbr;

	informationes->path = informationes->argv[0];
	if (informationes->lc_flag == 1)
	{
		informationes->lines++;
		informationes->lc_flag = 0;
	}
	for (i = 0, words_nbr = 0; informationes->arg[i]; i++)
		if (!is_delimiter(informationes->arg[i], " \t\n"))
			words_nbr++;

	if (!words_nbr)
		return;
	pathh = check_file_in_path(informationes, _getenv(informationes, "PATH="), informationes->argv[0]);
	if (pathh)
	{
		informationes->path = pathh;
		create_process(informationes);
	}
	else
	{
		if ((from_terminal(informationes) || _getenv(informationes, "PATH=") || informationes->argv[0][0] == '/') && is_executable(informationes, informationes->argv[0]))
			create_process(informationes);
		else if (*(informationes->arg) != '\n')
		{
			informationes->status = 127;
			print_error(informationes, "not found\n");
		}
	}
}
