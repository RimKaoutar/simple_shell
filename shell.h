#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

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

/* builtins_1.c */
int handle_exit(shell_t *);
int handle_help(shell_t *);
int handle_history(shell_t *);
int handle_cd(shell_t *);

/* builtins_2.c */
int unset_alias(shell_t *, char *);
int set_alias(shell_t *, char *);
int print_alias(list_t *);
int change_alias(shell_t *);
int handle_alias(shell_t *);

/* builtins_input.c */
ssize_t input_buf(shell_t *, char **, size_t *);
ssize_t read_buf(shell_t *, char *, size_t *);
ssize_t get_input(shell_t *);
int _getline(shell_t *, char **, size_t *);
void handle_sigint(int);

/* command_checker.c */
int change_string(char **, char *);
int change_v(shell_t *);
void check_chain(shell_t *, char *, size_t *, size_t, size_t);
bool is_chain(shell_t *, char *, size_t *);

/* command.c */
int handle_builtin(shell_t *);
void create_process(shell_t *);
int shell_main(shell_t *, char **);
void check_command(shell_t *);

/* env_functions_1.c */
char *_getenv(shell_t *, const char *);
int check_setenv(shell_t *);
int _printenv(shell_t *);
int check_unsetenv(shell_t *);
int gather_env(shell_t *);

/* env_functions_2.c */
char **get_environ(shell_t *);
int _unsetenv(shell_t *, char *);
int _setenv(shell_t *, char *, char *);

/* errors_fonctions.c */
void puts_err(char *);
int putchar_err(char);
int write_char(char , int);
int write_chars(char *, int);

/* helpers.c */
int from_terminal(shell_t *);
int _isalpha(int);
bool is_delimiter(char, char *);
int _atoi(char *);

/* history.c */
char *read_hist(shell_t *);
int create_history(shell_t *);
int renumber_history(shell_t *);
int read_history(shell_t *);
int update_history(shell_t *, char *, int);

/* initialization.c */
void set_zeros(unsigned int *, size_t);
void set_nulls(char *, size_t);

/* list_utils_1.c */
size_t _listlen(const list_t *);
char **list_to_vector(list_t *);
size_t print_list(const list_t *);
list_t *node_str_start(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* list_utils_2.c */
list_t *add_node_start(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_ttr(const list_t *);
int delete_node_at_index(list_t **, unsigned);
void free_list(list_t **);

/* memory_utils.c */
char *_memset(char *, char, unsigned);
void free_vector(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);

/* path_utils.c */
char *check_file_in_path(shell_t *, char *, char *);
bool is_executable(shell_t *, char *);
char *dup_chars(char *, int, int);

/* shell_info.c */
void clear_info(shell_t *);
void set_info(shell_t *, char **);
void free_info(shell_t *, int);

/* shell_utils.c */
int err_num(char *);
void print_error(shell_t *, char *);
void handle_comments(char *);
int print_dec(int, int);
char *change_base(long int, int, int);

/* string_functions_1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
int _putchar(char);
void _puts(char *);

/* string_functions_2.c */
char **strtow(char *, char *);
char **split_string(char *, char *, size_t *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* string_functions_3.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* words_coount.c */
int words_count(char *, char *, unsigned int *);

#endif /* SHELL_H */
