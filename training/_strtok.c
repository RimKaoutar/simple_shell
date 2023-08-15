#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


char **splitstr(char *str)
{
	char *token, **tokens = NULL;
	int count = 0, i;


	token = strtok(str, " \t\n");
	while (token)
	{
		count++;
		tokens = realloc(tokens, count * sizeof(char *));
		if (!tokens)
		{
			perror("realloc couldn't alloc :(");
			exit(EXIT_FAILURE);
		}
		tokens[count - 1] = token;
		token = strtok(NULL, " \t\n");
	}
	/*for (i = 0; i < count; i++)
		printf("%s\n", tokens[i]);*/
	return (tokens);
}

int main(int ac, char **av)
{
	char *line = NULL, **tokens;
	size_t len = 0;
	ssize_t nread;
	int i;

	(void)ac;
	(void)av;
	write(1, "$ ", 2);
	nread = getline(&line, &len, stdin);
	if (nread == EOF)
		perror("getline has reached end of file!\n");

	tokens = splitstr(line);
	for (i = 0; i < 3; i++)
		printf("%s\n", tokens[i]);
	return (0);
}
