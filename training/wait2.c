#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - fork & wait example
 *
 * Return: Always 0.i
 */
int main(void)
{
	pid_t child_pid;
	int status, i;
	char *argv[] = {"/bin/ls", "-l", "/tmp/", NULL};

	for (i = 0; i < 5; i++)
	{
		child_pid = fork();

		if (child_pid == -1)
		{
			perror("Error:");
			return (1);
		}
		if (child_pid == 0)
		{
			sleep(2);
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("Error in execve");
			}
		}
		else
		{
			wait(&status);
			printf("why you're always late? BAKA!\n"
				"I'm your father (%u)\n", child_pid);
		}
	}
	
	return (0);
}

