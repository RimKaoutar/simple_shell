#include "shell.h"
/* modified */
/**
 * unset_alias - set alias
 * @info: shell strct
 * @string: string
 * Return: 0 or 1
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
 * set_alias - revers of unset alias
 * @info: shell struct
 * @str: str
 * Return: 0 or 1
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
 * print_alias - puts alias
 * @neud: the done
 * Return: 0 1
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
 * change_alias - chenging the alias
 * @infro: the shell params
 * Return: iether 1 or 0
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
 * handle_alias - mimics alias
 * @infro: the shel paramas pointer to strct
 *	Return: 0
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
