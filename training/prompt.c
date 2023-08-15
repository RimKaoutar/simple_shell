#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
		  
	(void)ac;
	(void)av;
	write(1, "$ ", 2);
	nread = getline(&line, &len, stdin);
	if (nread == EOF)
		perror("getline has reached end of file!\n");

	/*line[len - 1] = '\0';*/
	printf("%s\n", line);
	return (0);
}
