#include "shell.h"

/**
 * clear_info - Clears the argument info structure
 * @shell: Pointer to the info structure to clear
 *
 * Description:
 * Sets all fields of the info structure to NULL or 0.
 * Resets the structure to contain no arguments.
 *
 * Return: Nothing.
 */
void clear_info(shell_t *shell)
{
	shell->arg = NULL;
	shell->argv = NULL;
	shell->path = NULL;
	shell->argc = 0;
}
/**
 * set_info - Sets argument info structure from argument array
 * @shell: Info structure pointer
 * @av: Argument array
 *
 * Description:
 * Sets program name from first arg
 * Splits arg string into argv array
 * Counts argv elements into argc
 * Applies alias and environment substitutions
 *
 * Return: Nothing.
 */
void set_info(shell_t *shell, char **av)
{
	int i = 0;

	shell->prog_name = av[0];

	if (shell->arg)
	{
		shell->argv = strtow(shell->arg, " \t");
		if (!shell->argv)
		{
			shell->argv = malloc(sizeof(char *) * 2);
			if (shell->argv)
			{
				shell->argv[0] = _strdup(shell->arg);
				shell->argv[1] = NULL;
			}
		}
		while (shell->argv && shell->argv[i])
		{
			i++;
		}
		shell->argc = i;
		change_alias(shell);
		change_v(shell);
	}
}
/**
 * free_info - Frees memory used by the info structure
 * @shell: Info structure to free
 * @free_all: Flag to fully free internal data
 *
 * Description:
 * Frees argv vector and sets pointers to NULL.
 * If free_all, it additionally:
 * Frees arg string
 * Frees linked lists
 * Frees environment vector
 * Closes file descriptors
 *
 * Return: Nothing.
 */
void free_info(shell_t *shell, int free_all)
{
	free_vector(shell->argv);
	shell->argv = NULL;
	shell->path = NULL;
	if (free_all)
	{
		if (!shell->sep_buff)
		{
			free(shell->arg);
		}
		if (shell->env)
		{
			free_list(&(shell->env));
		}
		if (shell->history)
		{
			free_list(&(shell->history));
		}
		if (shell->alias)
		{
			free_list(&(shell->alias));
		}
		free_vector(shell->environ);
		shell->environ = NULL;
		bfree((void **)shell->sep_buff);

		if (shell->fd_read > 2)
		{
			close(shell->fd_read);
		}
		_putchar(NEG_ONE);
	}
}
