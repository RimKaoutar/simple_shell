#include "shell.h"
/**
 * _split_str_prime - will call splistr multiple times
 * for handling the ";"
 * @line_buffer: the line buffer
 * Return: the array of arrays of strings
*/

char ***split_str_prime(char *line_buffer)
{
	char *f_token, *token_copy;
	char ***token_of_tokens = malloc(sizeof(char**) * 1024);
	int i = 0;

	f_token = _strtok_r(strdup(line_buffer), ";\n", &token_copy);
	while (f_token)
	{
		token_of_tokens[i] = splitstr(f_token);
		f_token = _strtok_r(NULL, ";\n", &token_copy);
		i++;
	}
	token_of_tokens[i] = NULL;
	return (token_of_tokens);
}
