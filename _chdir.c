#include "shell.h"
#include <linux/limits.h>
/**
 * _dir_ch - changes a dir
 * @command: the command arg
 * @Return: 0 on success -1 on error
*/
int change_dir(char **command, char **envp)
{
	(void) envp;
	int val = -1;
	char cwd[PATH_MAX];


	if (command[1] == NULL)
	{
		val = chdir(_getenv("HOME", envp));
	}
	else if (_strcmp(command[1], "-") == 0)
	{
		val = chdir(_getenv("OLDPWD", envp));
	}
	else
	{
		val = chdir(command[1]);
	}
	if (val == -1)
	{
		perror("cd");
		return (-1);
	}
	else if (val != -1)
	{
		getcwd(cwd, sizeof(cwd));
		_setenv("OLDPWD", _getenv("PWD", envp), 1);
		_setenv("PWD", cwd, 1);
	}
	return (0);
}