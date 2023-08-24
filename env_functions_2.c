#include "shell.h"

/**
 * get_environ - Returns environ array from environment list
 * @irnfo: Info structure containing environment
 *
 * Description:
 * Checks if environ array needs updating from linked list
 * If so, calls list_to_vector() to convert list to array
 * Resets changed flag after conversion
 *
 * Return: Pointer to environ array
*/
char **get_environ(shell_t *irnfo)
{
	if (!irnfo->environ || irnfo->env_changed)
	{
		irnfo->environ = list_to_vector(irnfo->env);
		irnfo->env_changed = 0;
	}

	return (irnfo->environ);
}

/**
 * _unsetenv - Unsets an environment variable from linked list
 * @info: Info structure containing environment list
 * @varibal: Variable name to unset
 *
 * Description:
 * Loops linked list to find matching variable
 * Calls delete_node_at_index() to remove matched node
 * Sets changed flag if removed
 *
 * Return: Changed flag status
*/
int _unsetenv(shell_t *info, char *varibal)
{
	list_t *neud = info->env;
	size_t i = 0;
	char *p;

	if (!neud || !varibal)
		return (0);
	while (neud)
	{
		p = starts_with(neud->str, varibal);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			neud = info->env;
			continue;
		}
		neud = neud->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Sets an environment variable in the linked list
 * @info: Info structure containing environment list
 * @va: Variable name
 * @val: Variable value
 *
 * Description:
 * Allocates a buffer with name=value
 * Loops list to find/update existing variable
 * Adds new node if not found
 * Frees buffer and sets changed flag
 *
 * Return: 0 on success, else 1.
*/

int _setenv(shell_t *info, char *va, char *val)
{
	char *buffer = NULL, *p;
	list_t *neu;

	if (!va || !val)
		return (1);
	buffer = malloc(_strlen(va) + _strlen(val) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, va);
	_strcat(buffer, "=");
	_strcat(buffer, val);
	neu = info->env;
	while (neu)
	{
		p = starts_with(neu->str, va);
		if (p && *p == '=')
		{
			free(neu->str);
			neu->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		neu = neu->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
