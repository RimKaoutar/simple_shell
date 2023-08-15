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
		{
			exec1(chars_nbr, line_buff);
		}
	}	
}

/**
 * exec1 - this function is specifically made for task 1
 * @chars_nbr: the number of chars printed to getline
 * @line_buff: the line buffer
*/
void exec1(ssize_t chars_nbr, char * line_buff)
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
