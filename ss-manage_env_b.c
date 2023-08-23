#include "shell.h"
/* modified */
/**
 * _getenv - like getenv
 * @inforr: params of shell
 * @nom: variable kay nom
 * Return: its value
*/
char *_getenv(info_s *inforr, const char *nom)
{
	char *p;
	list_s *neud = inforr->env;

	while (neud)
	{
		p = starts_with(neud->str, nom);
		if (p && *p)
			return (p);
		neud = neud->next;
	}
	return (NULL);
}

/**
 * check_setenv - checker for the funct setenv.
 * @infoe: params of shell stuct
 * Return: 1 or 0
*/
int check_setenv(info_s *infoe)
{
	if (infoe->argc != 3)
	{
		puts_err("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(infoe, infoe->argv[1], infoe->argv[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * _printenv - this function will print all the environ
 * @infro: the params of shel
 * Return: nada
*/
int _printenv(info_s *infro)
{
	print_list_str(infro->env);

	return (0);
}

/**
 * check_unsetenv - Rremove var env
 * @infot: params of shell
 * Return: 0
*/
int check_unsetenv(info_s *infot)
{
	int iz = 1;

	if (infot->argc == 1)
	{
		puts_err("Too few arguements.\n");
		return (1);
	}
	while (iz <= infot->argc)
	{
		_unsetenv(infot, infot->argv[iz]);
		iz++;
	}
	return (0);
}

/**
 * gather_env - env
 * @inefo: shell params struct
 * Return: 0 on success
*/
int gather_env(info_s *inefo)
{
	size_t i = 0;
	list_s *neud = NULL;

	while (environ[i])
	{
		add_node_end(&neud, environ[i], 0);
		i++;
	}

	inefo->env = neud;
	return (0);
}


