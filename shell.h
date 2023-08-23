#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <math.h>
#include <dirent.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>

#define HIST_FILE_NAME ".my_history"
#define NEG_ONE -1
#define USE_STRTOK 0
#define BUFFER_SIZE_READ 1024
#define BUFFER_SIZE_WRITE 1024
#define REG_FLAG 0
#define OR_FLAG 1
#define MAX_WORD_COUNT 100
#define HIST_SIZE_MAX 4096
#define BAS_CHANGE_UNSIG 2
#define BAS_CHANGE_LOWER 1
#define CHAIN_FLAG 3
#define AND_FLAG 2
#define SET_INFO							\
	{										\
		NULL, NULL, NULL, 0, 0, 0, 0,		\
		NULL, NULL, NULL, NULL, NULL,		\
		0, 0, NULL, 0, 0, 0					\
	}

extern char **environ;

/**
 * struct ListNode - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 * 
 * Description:
 * Defines a struct for use as nodes in a doubly linked list.
 * Used to store environment variables, history etc. as lists.
 */
typedef struct ListNode
{
	int num;
	char *str;
	struct ListNode *next;
} list_t;

/**
 * struct InfoNode - Struct containing shell execution details
 * @arg: the args
 * @argv: the arrays of strings rated form arts
 * @path: the path string for the current command
 * @argc: the number of arguments
 * @lines: the number of errors encountered
 * @error_code: the e error code
 * @lc_flag: a flag indicating wther this line of input should be counted
 * @prog_name: the name of the program's file
 * @env: the environ
 * @environ: a custom-modified copy of the eniron from the linked list env
 * @history: hystory
 * @alias: the node for the command alias
 * @env_changed: a flagtether environ has been changed
 * @status: the return status of the most recent executed command
 * @sep_buff: the address of the pointer to sep_buff, used for chaining
 * @sep_buff_kind: the type ofcmdnd buffer (CMD_type ||, &&, ;)
 * @fd_read: the file descriptor used for reading line input
 * @hist_lines: the number of ls in the history
 * 
 * Description:
 * Main struct used to store and pass info between functions
 * Fields contain command info, environment details and flags
 */
typedef struct InfoNode
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	size_t lines;
	int error_code;
	int lc_flag;
	char *prog_name;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **sep_buff;
	int sep_buff_kind;
	int fd_read;
	int hist_lines;
} shell_t;

/**
 * struct builtin - struct b
 * @type: the type
 * @func: the function ptr
 * 
 * Description:
 * Used to store name and function pointer for each builtin command
 * Allows builtins to be easily added/removed from the builtin handler
 */

typedef struct builtin
{
	char *type;
	int (*func)(shell_t *);
} builtin_commands;

int shell_main(shell_t *info, char **av);
int write_char(char c, int fd);
int write_chars(char *str, int fd);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
int putchar_err(char);
int _putchar(char);
int _isalpha(int);
int _atoi(char *);
int err_num(char *);
int handle_exit(shell_t *);
int handle_cd(shell_t *);
int handle_help(shell_t *);
int handle_history(shell_t *);
int handle_alias(shell_t *);
int _getline(shell_t *, char **, size_t *);
int _printenv(shell_t *);
int check_setenv(shell_t *);
int check_unsetenv(shell_t *);
int _unsetenv(shell_t *, char *);
int _setenv(shell_t *, char *, char *);
void puts_err(char *);
void _puts(char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_memset(char *, char, unsigned int);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getenv(shell_t *, const char *);
char *starts_with(const char *, const char *);
char *dup_chars(char *, int, int);
char *check_file_in_path(shell_t *info, char *pathstr, char *cmd);
char *change_base(long int, int, int);
char *read_hist(shell_t *info);
char **get_environ(shell_t *);
void free_vector(char **);
void print_error(shell_t *, char *);
void handle_comments(char *);
void free_list(list_t **);
void check_chain(shell_t *info, char *buf, size_t *p, size_t i, size_t len);
int handle_builtin(shell_t *);
bool is_executable(shell_t *, char *);
int loophsh(char **);
int bfree(void **);
int from_terminal(shell_t *);
int print_dec(int, int);
int gather_env(shell_t *);
int create_history(shell_t *info);
int read_history(shell_t *info);
int update_history(shell_t *info, char *buf, int linecount);
int renumber_history(shell_t *info);
int delete_node_at_index(list_t **, unsigned int);
bool is_chain(shell_t *, char *, size_t *);
int change_alias(shell_t *);
int change_v(shell_t *);


char **strtow(char *, char *);
char **list_to_vector(list_t *);
void check_command(shell_t *);
void create_process(shell_t *);
void handle_sigint(int);
void clear_info(shell_t *);
void set_info(shell_t *, char **);
void free_info(shell_t *, int);

int change_string(char **, char *);
list_t *add_node_start(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
list_t *node_str_start(list_t *, char *, char);
size_t print_list_ttr(const list_t *);
size_t _listlen(const list_t *);
size_t print_list(const list_t *);
ssize_t get_input(shell_t *);
ssize_t get_node_index(list_t *, list_t *);
char **split_string(char *str, char *separators, size_t *word_count);
int words_count(char *str, char *separators, unsigned int *arr);
void set_zeros(unsigned int *arr, size_t size);
void set_nulls(char *arr, size_t size);
bool is_delimiter(char c, char *delimiters);

#endif /* SHELL_H */
