#include "shell.h"

/**
 * handle_exit - Handles the exit builtin command
 * @infeo: Info structure containing command args
 * 
 * Description:
 * Checks for an argument and passes to err_num()
 * Prints error and sets status if not a valid number
 * Returns exit code based on parsed number or default
 * 
 * Return: -2 to exit program, 1 if err
*/
int handle_exit(shell_t *infeo)
{
	int exx_check;

	if (infeo->argv[1])
	{
		exx_check = err_num(infeo->argv[1]);
		if (exx_check == -1)
		{
			infeo->status = 2;
			print_error(infeo, "Illegal number: ");
			puts_err(infeo->argv[1]);

			putchar_err('\n');
			return (1);
		}
		infeo->error_code = err_num(infeo->argv[1]);
		return (-2);
	}

	infeo->error_code = -1;
	return (-2);
}

/**
 * handle_help - Handles printing help for builtin commands
 * @infto: Info structure containing command args
 * 
 * Description:
 * Currently just prints a placeholder message that
 * the function is not supported yet.
 * Eventually it will need to be updated to:
 * Check for a command name argument
 * Print help text for the specified command
 * Print generic help if no command given
 * 
 * Return: 0 for success
*/
int handle_help(shell_t *infto)
{
	char **rr_arr;

	rr_arr = infto->argv;
	_puts("Function is not supported yet. \n");
	if (0)
		_puts(*rr_arr);
	return (0);
}

/**
 * handle_history - Handles printing the command history
 * @infto: Info structure containing command history
 * 
 * Description:
 * Prints out the full command history linked list
 * By calling print_list() on the history pointer
 * Currently just a simple print, could eventually
 * support additional history manipulation.
 * 
 * Return: 0 for success
*/
int handle_history(shell_t *infto)
{
	print_list(infto->history);

	return (0);
}

/**
 * handle_cd - Handles changing working directory
 * @inefo: Info structure containing command args
 * 
 * Description:
 * Gets current working directory
 * Handles home, - and regular directory options
 * Calls chdir() and sets PWD/OLDPWD variables
 * Prints error if chdir fails
 * 
 * Returns 0 on success
*/
int handle_cd(shell_t *inefo)
{
	char *s, *dir, buff[1024];
	int ink_what_to;

	s = getcwd(buff, 1024);
	if (!s)
		_puts("UPGRADE:getcwd failure message\n");
	if (!inefo->argv[1])
	{
		dir = _getenv(inefo, "HOME=");
		if (!dir)
			ink_what_to =
				chdir((dir = _getenv(inefo, "PWD=")) ? dir : "/");
		else
			ink_what_to = chdir(dir);
	}
	else if (_strcmp(inefo->argv[1], "-") == 0)
	{
		if (!_getenv(inefo, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inefo, "OLDPWD=")), _putchar('\n');
		ink_what_to =
			chdir((dir = _getenv(inefo, "OLDPWD=")) ? dir : "/");
	}
	else
		ink_what_to = chdir(inefo->argv[1]);

	if (ink_what_to == -1)
	{
		print_error(inefo, "can't cd to ");
		puts_err(inefo->argv[1]), putchar_err('\n');
	}
	else
	{
		_setenv(inefo, "OLDPWD", _getenv(inefo, "PWD="));
		_setenv(inefo, "PWD", getcwd(buff, 1024));
	}
	return (0);
}
