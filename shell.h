#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* globle variables */
#define BUF_SIZE 1024
#define BUF_FLUSH -1
#define CHAIN_CMD 3
#define AND_CMD 2
#define OR_CMD 1
#define NORM_CMD 0
#define TO_LOWERCASE 1
#define TO_UNSIGNED 2
#define HISTORY_FILE ".simple_shell_history"
#define MAX_HIST_COUNT 4096

extern char **environ;

/**
 * struct node_list - singly linked list node for alias management
 * @num: a numerical identifier for the node
 * @str: a string that represents the alias
 * @next: pointer to the next node in the list
 */
typedef struct node_list
{
int num;
char *str;
struct node_list *next;
} node_t;

/**
 * struct sh_data - stores data required for shell operation
 *                  allows uniform prototype for function pointers
 * @input: a string generated from getline containing arguments
 * @args: an array of strings generated from arg
 * @exec_path: a string path for the current command
 * @file_name: the program filename
 * @env: linked list local copy of environment variables
 * @hist: the history linked list node
 * @alias: the alias linked list node
 * @environ: custom modified copy of environment variables derived from env
 * @chain_buf: pointer to the command buffer, used for command chaining
 *
 * @arg_count: the number of arguments
 * @line_num: the count of lines processed (for error tracking)
 * @exit_code: the error code used for exit()
 * @line_flag: flag indicating if the current line should be counted
 * @env_modified: flag indicating if the environment was modified
 * @last_status: the return status of the last executed command
 * @chain_type: the type of command chaining (e.g., ||, &&, ;)
 * @input_fd: the file descriptor from which to read input
 * @hist_num: the total number of lines in the command history
 */
typedef struct sh_data
{
char *input;
char **args;
char *exec_path;
char *file_name;
node_t *env;
node_t *hist;
node_t *alias;
char **environ;
char **chain_buf;

int arg_count;
unsigned int line_num;
int exit_code;
int line_flag;
int env_modified;
int last_status;
int hist_num;
int chain_type;
int input_fd;
} data_t;

#define INIT_DATA \
{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, \
	0, 0, 0, 0, 0, 0, 0, 0, 0}

/**
 * struct builtins - contains a built-in command and its associated function
 * @cmd_name: the name of the built-in command
 * @execute: the function that executes the built-in command
 */
typedef struct builtins
{
	char *cmd_name;
	int (*execute)(data_t *);
} builtins_t;

/* aliases.c file */
int unset_alias(data_t *data, char *str);
int set_alias(data_t *data, char *str);
int print_alias(node_t *node);

/* builtins.c file */
int b_exit(data_t *data);
int b_cd(data_t *data);
int b_help(data_t *data);
int b_history(data_t *data);

/* builtins2.c file */
int b_alias(data_t *data);
int b_env(data_t *data);
int b_setenv(data_t *data);
int b_unsetenv(data_t *data);

/* cmd_chain.c file */
int is_chain_delim(data_t *data, char *buf, size_t *pos);
void chain_continue(data_t *, char *, size_t *, size_t, size_t);

/* converters.c file */
char **split_str(char *str, char *d);
char *int_to_string(long int num, int base, int flags);
int str_to_int(char *str);

/* environment.c file */
char *env_get(data_t *data, const char *name);
int env_to_list(data_t *data);
char **env_to_arr(data_t *data);
int env_remove(data_t *data, char *var);
int env_init(data_t *data, char *var, char *value);

/* print_error.c file */
void print_to_stderr(char *str);
int print_char_stderr(char c);
void print_error(data_t *data, char *errstr);
int print_int(int num, int fd);

/* error_handler.c file */
void rm_comments(char *buf);
int write_char_fd(char c, int fd);
int write_str_fd(char *str, int fd);

/* history.c file */
int hist_create(data_t *data);
char *hist_file(data_t *data);
int hist_adds_entry(data_t *data, char *buf, int linecount);
int hist_adjust(data_t *data);
int hist_read(data_t *data);

/* input_handlers.c file */
ssize_t input_buf(data_t *data, char **buf, size_t *len);
ssize_t input_get_line(data_t *data);
ssize_t read_buf(data_t *data, char *buf, size_t *i);
int input_next_line(data_t *data, char **ptr, size_t *length);
void sig_handler(__attribute__((unused)) int sig_num);

/* linked_list.c file */
node_t *list_append(node_t **head, const char *str, int num);
size_t list_size(const node_t *head);
char **list_to_strs(node_t *head);
size_t list_print(const node_t *h);
node_t *list_find_start(node_t *node, char *prefix, char c);

/* linked_list2.c file */
ssize_t list_get_index(node_t *head, node_t *node);
size_t list_print_strs(const node_t *head);
int list_del_at(node_t **head, unsigned int index);
void list_free(node_t **listhead);

/* memory_utils.c file */
char *mem_set(char *memptr, char b, unsigned int num);
int free_ptr(void **ptr);
void free_arr(char **strsptr);
void *mem_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* path_handlers file */
char *locate_cmd(data_t *data, char *pathstr, char *cmd);
int is_exec(data_t *data, char *path);
char *dup_chars(char *pathstr, int start, int stop);

/* shell_data.c file */
void clear_data(data_t *data);
void set_data(data_t *data, char **av);
void free_data(data_t *data, int all);

/* shell_exec.c file */
int hsh(data_t *data, char **av);
int lookup_builtin(data_t *data);
void search_cmd(data_t *data);
void fork_and_exec(data_t *data);

/* string_utils.c file */
int is_delim(char c, char *delim);
int str_len(char *str);
int str_cmp(char *str1, char *str2);
char *str_starts(const char *haystack, const char *prefix);

/* string_utils2.c file */
char *str_cat(char *dest, char *src);
char *str_cpy(char *dest, char *src);
char *str_dup(const char *str);
void print_str(char *str);

/* string_utils3.c file */
int put_char(char c);
char *str_ncpy(char *dest, char *src, int num);
char *str_ncat(char *dest, char *src, int num);
char *str_chr(char *str, char c);

/* var_handlers.c file */
int expand_alias(data_t *data);
int expand_var(data_t *data);
int expand_str(char **oldstr, char *newstr);

#endif
