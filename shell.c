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
int main()
{
	int is_interactive = 1;
	char *line_buffer = NULL;
	ssize_t chars_nbr;
	size_t n = 0, task_id = 2;
	pid_t weldi;

	while (is_interactive)
	{
		is_interactive = check_interactivity();
		write (STDOUT_FILENO, "$ ", 2);
		chars_nbr = getline(&line_buffer, &n, stdin);
		if (chars_nbr == -1)
		{
			free(line_buffer);
			perror("getline");
			exit(EXIT_FAILURE);
		}
		if (chars_nbr != EOF)
		{
			weldi = fork();
			if (weldi == -1)
			{
				free(line_buffer);
				perror("weldi mat");
				exit(EXIT_FAILURE);
			}
			if (weldi == 0)
				executionner(chars_nbr, line_buffer, task_id);
			else
				wait(NULL);
		}
	}
	free(line_buffer);
	return (0);
}
