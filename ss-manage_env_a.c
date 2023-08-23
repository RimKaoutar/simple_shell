#include "shell.h"
/* modified */
/**
 * get_environ - gets the environ vars
 * @irnfo: params of the shelll
 * Return: The environment variables as an array of strings.
*/
char **get_environ(info_s *irnfo)
{
	if (!irnfo->environ || irnfo->env_changed)
	{
		irnfo->environ = list_to_vector(irnfo->env);
		irnfo->env_changed = 0;
	}

	return (irnfo->environ);
}

/**
 * _unsetenv - usets enf
 * @info: shell params structure
 * @varibal: varibaliable.
 * Return: 1 on sec, 0 if else
*/
int _unsetenv(info_s *info, char *varibal)
{
	list_s *neud = info->env;
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
 * _setenv - set an env var
 * @info: params shell struct
 * @var: the key
 * @val: val
 * Return: 0 on suc; 1 if else
*/

int _setenv(info_s *info, char *va, char *val)
{
	char *buffer = NULL, *p;
	list_s *neu;

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


