#include "shell.h"
/* modified */

/**
 * change_string - changes str
 * @django_unchaned: address of django_unchaned string
 * @the_wolf_of_wall_street: the_wolf_of_wall_street string
 * Return: 1 or 0
*/
int change_string(char **django_unchaned, char *the_wolf_of_wall_street)
{
	free(*django_unchaned);
	*django_unchaned = the_wolf_of_wall_street;

	return (1);
}

/**
 * check_chain - check broj
 * @information: info strct
 * @buf: buffer
 * @pp: ptr to addr in buf
 * @i: i
 * @legn:  len
 * Return: nada
*/
void check_chain(info_s *information, char *bbuf, size_t *pp, size_t i, size_t legn)
{
	size_t jj = *pp;

	if (information->sep_buff_kind == AND_FLAG)
	{
		if (information->status)
		{
			bbuf[i] = 0;
			jj = legn;
		}
	}

	if (information->sep_buff_kind == OR_FLAG)
	{
		if (!information->status)
		{
			bbuf[i] = 0;
			jj = legn;
		}
	}
	*pp = jj;
}

/**
 * is_chain - test the chain
 * @information: information struct
 * @bufferr: the char bufferrfer
 * @p: address of cu
 * Return: 1 or 0
*/
bool is_chain(info_s *information, char *bufferr, size_t *p)
{
	size_t j = *p;

	if (bufferr[j] == '|' && bufferr[j + 1] == '|')
	{
		bufferr[j] = 0;
		j++;
		information->sep_buff_kind = OR_FLAG;
	}
	else if (bufferr[j] == '&' && bufferr[j + 1] == '&')
	{
		bufferr[j] = 0;
		j++;
		information->sep_buff_kind = AND_FLAG;
	}
	else if (bufferr[j] == ';')
	{
		bufferr[j] = 0;
		information->sep_buff_kind = CHAIN_FLAG;
	}
	else
		return (false);
	*p = j;
	return (true);
}

/**
 * change_v - replacer
 * @inforrrmation: the strct
 * Return: 1 or 0 bruh
*/
int change_v(info_s *inforrrmation)
{
	int iy = 0;
	list_s *noede;

	for (iy = 0; inforrrmation->argv[iy]; iy++)
	{
		if (inforrrmation->argv[iy][0] != '$' || !inforrrmation->argv[iy][1])
			continue;
		if (!_strcmp(inforrrmation->argv[iy], "$?"))
		{
			change_string(&(inforrrmation->argv[iy]),

						   _strdup(change_base(inforrrmation->status, 10, 0)));

			continue;
		}
		if (!_strcmp(inforrrmation->argv[iy], "$$"))
		{
			change_string(&(inforrrmation->argv[iy]),

						   _strdup(change_base(getpid(), 10, 0)));

			continue;
		}
		noede = node_str_start(inforrrmation->env, &inforrrmation->argv[iy][1], '=');
		if (noede)
		{
			change_string(&(inforrrmation->argv[iy]),

						   _strdup(_strchr(noede->str, '=') + 1));

			continue;
		}
		change_string(&inforrrmation->argv[iy], _strdup(""));
	}
	return (0);
}

