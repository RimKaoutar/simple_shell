#include "shell.h"
/* modified */

/**
 * main - the main
 * @argc: nbr of args
 * @argv: the args
 * Return: 0 or 1
*/
int main(int argc, char **argv)
{
	info_s infoe[] = {SET_INFO};
	int fd = 2;

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
				puts_err(": 0: Can't open ");
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
