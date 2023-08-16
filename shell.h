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

char **parse_input(char *input);
void execute_command(char **tokens, char *prog, int l_num);
char *search_path(char *cmd, path_t *path_list);
char *_getenv(const char *name);
path_t *parse_path(void);
void free_path_list(path_t *head);
void direct_execute(char **tokens, char *prog, int l_num);
void path_execute(char **tokens, char *prog, int l_num);
char **init_token(void);
void check_allocation(char **tokens);
char **resize_token_buffer(char **tokens, size_t *bufsize);
int exe_cmd_with_path(char *f_path, char **toks, char *prog, int l_num);

#endif
