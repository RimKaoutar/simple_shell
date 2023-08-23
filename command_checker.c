#include "shell.h"

/**
 * change_string - Changes a string pointer to a new string
 * @django_unchaned: Pointer to existing string pointer
 * @the_wolf_of_wall_street: New string
 * 
 * Description:
 * Frees the memory of the existing string
 * Points the string pointer to the new string
 * 
 * Return: 1 to indicate success
*/
int change_string(char **django_unchaned, char *the_wolf_of_wall_street)
{
	free(*django_unchaned);
	*django_unchaned = the_wolf_of_wall_street;

	return (1);
}


/**
 * change_v - Changes environment variable references in argv
 * @inforrrmation: Info struct
 * 
 * Description:
 * Loops through argv checking for $var references
 * Handles $?, $$ by returning status/pid values
 * Looks up env vars and substitutes value if found
 * Handles not found by substituting empty string
 * 
 * Returns: 0 on success
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

/**
 * check_chain - Checks logical chain of commands and truncates buffer
 * @information: Info struct
 * @bbuf: Buffer being filled
 * @pp: Pointer to buffer index
 * @i: Current buffer index
 * @legn: Buffer length
 * 
 * Description:
 * Checks the AND/OR flag on info struct
 * Truncates buffer by adding NULL at index if
 * condition is met based on flag
 * Updates buffer index pointer
 * 
 * Return: Nothing
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
 * is_chain - Checks if logical chain separator is present in buffer
 * @information: Info struct
 * @bufferr: Command buffer
 * @p: Pointer to buffer index
 * 
 * Description:
 * Checks buffer character at index for chain separator
 * Handles ||, &&, ; separators
 * Sets flag on info struct and truncates buffer
 * Updates buffer index pointer
 * 
 * Return: True if separator found, false otherwise
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
