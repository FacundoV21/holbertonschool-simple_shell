#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>

extern char **environ;

#define BUFFER_SIZE 1024

/**
 * struct path_s - singly linked list to hold directories from PATH
 * @dir: directory path
 * @next: points to the next node
 */
typedef struct path_s
{
	char *dir;
	struct path_s *next;
} path_t;

int cleanup(char *input_line, int status, int fd_isatty);
void free_tokens(char **tokens);
char **parse_input(char *input);
char *search_path(char *cmd, path_t *path_list);
char *_getenv(const char *name);
void print_env(void);
path_t *parse_path(void);
path_t *create_new_node(char *token);
void append_to_list(path_t **head, path_t *new_node);
void free_path_list(path_t *head);
int execute_command(char **toks, char *prog, int l_num);
int exe_cmd_with_path(char *f_path, char **toks, char *prog, int l_num);
int direct_execute(char **tokens, char *prog, int l_num);
int path_execute(char **tokens, char *prog, int l_num);
char **init_token(void);
void check_allocation(char **tokens);
char **resize_token_buffer(char **tokens, size_t *bufsize);

#endif
