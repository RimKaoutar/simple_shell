#include "shell.h"
/**
 * unset_alias - Unsets an alias from the alias list
 * @info: Info struct containing aliases
 * @string: Alias name to unset
 * 
 * Description:
 * Finds the '=' in the alias name=value string
 * Terminates the string there to get just the name
 * Calls delete_node_at_index() to remove alias node
 * by name from the alias linked list
 * 
 * Return: Status from delete_node operation
*/
int unset_alias(info_s *info, char *string)
{
	char *p, c;
	int retr;

	p = _strchr(string, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	retr = delete_node_at_index(&(info->alias),
	get_node_index(info->alias, node_str_start(info->alias, string, -1)));
	*p = c;
	return (retr);
}

/**
 * set_alias - Sets or unsets an alias
 * @infro: Info struct containing aliases
 * @stzr: Alias name=value string
 * 
 * Description:
 * Finds '=' in string and increments to value
 * If no value, calls unset_alias to remove alias
 * Otherwise, removes existing alias then adds
 * new alias node with full name=value string
 * 
 * Return: 0 on success, 1 on failure
*/
int set_alias(info_s *infro, char *stzr)
{
	char *p;

	p = _strchr(stzr, '=');
	if (!p)
	{
		return (1);
	}
	if (!*++p)
		return (unset_alias(infro, stzr));

	unset_alias(infro, stzr);

	return (add_node_end(&(infro->alias), stzr, 0) == NULL);
}

/**
 * print_alias - Prints out an alias
 * @neud: Pointer to alias node in linked list
 * 
 * Description:
 * 
 * Finds '=' in alias string to separate name and value
 * Prints name up to '=' character
 * Prints value including surrounding ''
 * 
 * Return: 0 for success, 1 if no node
*/
int print_alias(list_s *neud)
{
	char *pr = NULL;
	char *a = NULL;

	if (neud)
	{
		pr = _strchr(neud->str, '=');
		for (a = neud->str; a <= pr; a++)
			_putchar(*a);
		_putchar('\'');

		_puts(pr + 1);
		_puts("'\n");
		return (0);
	}

	return (1);
}
/**
 * change_alias - Changes an alias to its expanded value
 * @infro: Info struct containing aliases and argument
 * 
 * Description:
 * Loops up to 10 times to recursively expand an alias
 * Finds matching alias node by name
 * Frees current argv[0] and replaces with alias value
 * Stop looping if no match or value found
 * 
 * Return: 1 if fully expanded, 0 if not expanded
*/
int change_alias(info_s *infro)
{
	int index;
	list_s *neud;
	char *p;

	for (index = 0; index < 10; index++)
	{
		neud = node_str_start(infro->alias, infro->argv[0], '=');
		if (!neud)
			return (0);
		free(infro->argv[0]);
		p = _strchr(neud->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		infro->argv[0] = p;
	}

	return (1);
}

/**
 * handle_alias - Handles alias commands
 * @infro: Info struct containing aliases and args
 * 
 * Description:
 * If 1 arg, prints all aliases
 * Else loops through args:
 * If '=' parses as alias definition
 * and calls set_alias()
 * Else prints matching alias
 * 
 * Return: 0 for success
*/
int handle_alias(info_s *infro)
{
	int i = 0;
	char *p = NULL;
	list_s *neud = NULL;

	if (infro->argc == 1)
	{
		neud = infro->alias;
		while (neud)
		{
			print_alias(neud);
			neud = neud->next;
		}
		return (0);
	}
	for (i = 1; infro->argv[i]; i++)
	{
		p = _strchr(infro->argv[i], '=');
		if (p)
			set_alias(infro, infro->argv[i]);
		else
			print_alias(node_str_start(infro->alias, infro->argv[i], '='));
	}

	return (0);
}
