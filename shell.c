#include "shell.h"
/**
 * check_interactivity - checks if the stdin was redirected by the terminal
 * or it is flushed
 * Return: 0 if it was redirected , not 0 if else
 */
int check_interactivity(void)
{
	return (isatty(STDIN_FILENO));
}

/**
 * main - the main function to sh
 * Return: 0 on exit_success
 */
int main(int ac, char **av, char **envp)
{
	int is_interactive = 1, i;
	char *line_buffer = NULL;
	ssize_t chars_nbr;
	size_t n = 0, task_id = 4;

	(void) ac, (void) av;
	while (is_interactive)
	{
		is_interactive = check_interactivity();
		write (STDOUT_FILENO, "$ ", 2);
		chars_nbr = _getline(&line_buffer, &n, stdin);
		if (chars_nbr == -1)
		{
			free(line_buffer);
			return(EXIT_FAILURE);
		}
		if (chars_nbr != EOF)
		{
			if ((i = checker(line_buffer, envp)) != 0)
			{
				if (i == 1)
					break;
				else
					continue;
			}
			executionner_prime(envp, line_buffer, task_id);
		}
	}
	free(line_buffer);
	exit(0);
}

void executionner_prime(char **envp, char *line_buffer, int task_id)
{
	char ***token_of_tokens;
	pid_t son;
	int stat, i = 0;

	token_of_tokens = split_str_prime(line_buffer);
	while (token_of_tokens[i])
	{
		son = fork();
		if (son == -1)
		{
			free(line_buffer);
			perror("son died");
			exit(EXIT_FAILURE);
		}
		if (son == 0)
		{
			executionner(line_buffer, task_id, envp, token_of_tokens[i]);
		}
		else
		{
			wait(&stat);
		}
		i++;
	}
	free(token_of_tokens);
}
