#include "shell.h"

/**
 * putline - puts a line out to the stdout using getline
 * @gr: the getline_return struct (contains a line_buffer char
 * and a charsnbr int)
 * Return: a struct of type getline_return that contains the number of chars
 * printed and contains the line_buffer
*/
getline_return* putline(getline_return *gr)
{
	int char_nbr;
	char *line_buff = NULL;
	size_t n = 0;
	write(1, "$ ", 2);

	char_nbr = getline(&line_buff, &n, stdin);
	if (char_nbr == -1)
	{
		perror("error");
	}
	gr->charsnbr = char_nbr;
	gr->line_buff = line_buff;
	return (gr);
}

/**
 * _getenv - based on the key that you give it , it will look in the enviroment file
 * for it , if found , it returns the value of this key , if not NULL
 * @path: usually we will only need path so imma name it path
 * Return: the value of path
*/
char *_getenv(const char *path)
{
	extern char **__environ;
	int i = 0;
	char *token;

	while (__environ[i])
	{
		token = strtok(__environ[i], "=");
		if (strcmp(token, path) == 0)
			return (strtok(NULL, "="));
		i++;
	}
	return (NULL);
}

/**
 * getargs - this function will parse the line buffer and create a 2d
 * array that contains whatever commands and args that were typed into
 * the line buffer using getline
 * @line_buff: the line buffer
 * Return: a 2d array containing the command in the first case and
 * the args in the other cases
*/
char **get_args(char *line_buff)
{
	char *token, **array = malloc(sizeof(char *) * 1024);
	int i = 0;	
	token = strtok(line_buff, " \n\t");
	while (token)
	{
		array[i] = token;
		token = strtok(NULL, " \t\n");
		i++;
	}
	array[i] = NULL;
	return (array);

}

/**
 * get_command - if your command was not a full path, this function does the job
 * @path: the path variable of your system
 * @cmd: the command you typed into getline
 * Return: either the full path of the command , or NULL
*/
char *get_command(char *path, char *cmd)
{
	char *token, *temp; 
	token = strtok(path, ":");

	while (token)
	{
		temp = malloc(sizeof(char) * (strlen(token) + 2 + strlen(cmd)));
		strcpy(temp, token);
		strcat(temp, "/");
		strcat(temp, cmd);
		if (access(temp, F_OK) == 0)
			return (temp);
		token = strtok(NULL, ":");
		free(temp);
	}
	return (NULL);
}