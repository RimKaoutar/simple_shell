#include "shell.h"

/**
 * main - Entry point of the shell program
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Description:
 * Initializes info struct and file descriptor
 * Opens file for reading if given as argv[1]
 * Sets up environment and history
 * Calls main shell loop
 * Exits cleanly
 *
 * Return: EXIT_SUCCESS (1) or EXIT_FAILURE (0)
*/
int main(int argc, char **argv)
{
	int fd = 2;
	shell_t infoe[] = {SET_INFO};

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fd)
		: "r"(fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);

			if (errno == ENOENT)
			{
				puts_err(argv[0]);
				puts_err(": 0: Can not open ");
				puts_err(argv[1]);
				putchar_err('\n');
				putchar_err(NEG_ONE);
				exit(127);
			}

			return (EXIT_FAILURE);
		}

		infoe->fd_read = fd;
	}

	gather_env(infoe);
	read_history(infoe);
	shell_main(infoe, argv);

	return (EXIT_SUCCESS);
}
