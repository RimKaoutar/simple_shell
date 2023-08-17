#include "shell.h"
/**
 * _executionner - this is the function that will do it all
 * @chars_nbr: the number of chars printed to getline
 * @line_buff: the line_buffer
 * @task_id: the task id to execute the right function for the right task
*/
void executionner(ssize_t chars_nbr, char *line_buff, int task_id)
{
	(void) chars_nbr;
	switch(task_id)
	{
		case 1:
			exec1(chars_nbr, line_buff);
			break;
		case 2:
			exec2(chars_nbr, line_buff);
			break;
	}	
}

/**
 * exec1 - this function is specifically made for task 1
 * @chars_nbr: the number of chars printed to getline
 * @line_buff: the line buffer
*/
void exec1(ssize_t chars_nbr, char *line_buff)
{
	char *one_token, *two_token;
	char *args[] = {NULL};

	(void) chars_nbr;
	one_token = strtok(line_buff, " \n\t");
	while (1)
	{
		two_token = strtok(NULL, " \t\n");
		if (!two_token)
			break;
		strcat(one_token, two_token);
	}

	if (one_token)
	{
		execve(one_token, args, NULL);
		perror("execve");
	}
}

/**
 * exec2 - task 2 funciton (the arguments array will be of size 1024,
 * we can reallocate it each time we need more but we still don't have realloc)
 * @chars_nbr: the number of chars printed to getline
 * @line_buff: the line buffer
*/
void exec2(ssize_t chars_nbr, char *line_buff)
{
	char **args = splitstr(line_buff);
	int i = 0;

	(void) chars_nbr;

	/*this loop is for debuging purpose only, will be omited when done*/
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
	if (args)
	{
		execve(args[0], args, NULL);
	}
}
