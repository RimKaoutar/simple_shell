#include "shell.h"
/**
 * _executionner - this is the function that will do it all
 * @line_buff: the line_buffer
 * @task_id: the task id to execute the right function for the right task
 * @envp: the envp
 * @token_of_tokens: the array of cmds
 */
void executionner(char *line_buff, int task_id, char **envp
, char **token_of_tokens)
{
	switch (task_id)
	{
		case 1:
			exec1(line_buff);
			break;
		case 2:
			exec2(line_buff);
			break;
		case 3:
			exec3(line_buff, envp);
			break;
		case 4:
			exec4(token_of_tokens, envp);
	}
}

/**
 * exec1 - this function is specifically made for task 1
 * @line_buff: the line buffer
 */
void exec1(char *line_buff)
{
	char *one_token, *two_token, *saveptr;
	char *args[] = {NULL};

	one_token = _strtok_r(line_buff, " \n\t", &saveptr);
	while (1)
	{
		two_token = _strtok_r(NULL, " \t\n", &saveptr);
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
 * @line_buff: the line buffer
 */
void exec2(char *line_buff)
{
	char **args = splitstr(line_buff);

	if (args)
	{
		execve(args[0], args, NULL);
	}
}

/**
 * exec3 - this function is specifically made for task 3
 * @line_buff: the line buffer
 * @envp: the env pointer
 */
void exec3(char *line_buff, char **envp)
{
	char **args = splitstr(line_buff);
	char *cmd;

	cmd = get_command(args[0], envp);
	if (cmd)
	{
		execve(cmd, args, envp);
		perror("cmd");
	}
	else
	{
		execve(args[0], args, NULL);
		perror("execve");
	}
}
/**
 * exec4 - this function will handle the ";" "&&" "#" and "||"
 * @token_of_tokens: this is an array of arrays of strings
 * @envp: the env pointer, again , extern is not allowed
*/
void exec4(char **token_of_tokens, char **envp)
{
	char *cmd;

	while (token_of_tokens)
	{
	cmd = get_command(token_of_tokens[0], envp);
	if (cmd)
	{
		execve(cmd, token_of_tokens, envp);
		perror("cmd");
	}
	else
	{
		execve(token_of_tokens[0], token_of_tokens, NULL);
		perror("execve");
	}
	}
}
