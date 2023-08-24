#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable
 * @inforr: Info structure containing environment list
 * @nom: Name of the environment variable
 *
 * Description:
 * Loops through the environment linked list
 * Calls starts_with() to check if variable matches name
 *
 * Return: pointer to value if found, else NULL
*/
char *_getenv(shell_t *inforr, const char *nom)
{
	char *p;
	list_t *neud = inforr->env;

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
 * check_setenv - Checks parameters and calls setenv
 * @infoe: Info structure containing arguments
 *
 * Description:
 * Validates argc is exactly 3
 * Calls _setenv() to set the environment variable
 * Prints error if validation or setenv fails
 * Provides a wrapper to validate setenv call
 *
 * Return: 0 on success, 1 on failure
*/
int check_setenv(shell_t *infoe)
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
 * _printenv - Prints the environment variables
 * @infro: Info structure containing environment list
 *
 * Description:
 * Prints out each environment variable by calling print_list_ttr()
 * on the environment linked list.
 *
 * Return: Always returns 0 to indicate success.
*/
int _printenv(shell_t *infro)
{
	print_list_ttr(infro->env);

	return (0);
}

/**
 * check_unsetenv - Validates and calls unsetenv for each argument
 * @infot: Info structure containing arguments
 *
 * Description:
 * Checks for minimum of 1 argument
 * Loops through arguments and calls _unsetenv()
 * Prints error if not enough args
 * Provides validation wrapper for unsetenv calls
 *
 * Return: 0 on success
*/
int check_unsetenv(shell_t *infot)
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
 * gather_env - Populates the environment list from environ array
 * @inefo: Info struct to populate environment variable list into
 *
 * Description:
 * Loops through the global environ array
 * Adds each entry as a new node to the linked list
 * Sets the info struct's env pointer to the list head
 *
 * Return: 0 on success
*/
int gather_env(shell_t *inefo)
{
	size_t i = 0;
	list_t *neud = NULL;

	while (environ[i])
	{
		add_node_end(&neud, environ[i], 0);
		i++;
	}

	inefo->env = neud;
	return (0);
}
