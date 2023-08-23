#include "shell.h"
/* modified */
/**
 * handle_exit - exit
 * @infeo: shell params
 * Return: exit with a status
*/
int handle_exit(info_s *infeo)
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
 * handle_help - handles the help cmd
 * @info: the paramsof shel
 * Return: 0
*/

int handle_help(info_s *infto)
{
	char **rr_arr;

	rr_arr = infto->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*rr_arr);
	return (0);
}

/**
 * handle_history - aficcher la liste de commnads
 * @infto: the shell pa
 * Return: 0
*/

int handle_history(info_s *infto)
{
	print_list(infto->history);

	return (0);
}

/**
 * handle_cd - its cd
 * @inefo: the params shell struct
 * Return: 0
*/
int handle_cd(info_s *inefo)
{
	char *s, *dir, buff[1024];
	int ink_what_to;

	s = getcwd(buff, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
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
