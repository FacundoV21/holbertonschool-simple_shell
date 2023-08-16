#include "shell.h"
/**
 * exe_cmd_with_path - Executes a command given its full path.
 * @f_path: The full path of the command.
 * @toks: The command and its arguments.
 * @prog: Program's name (argv[0]).
 * @l_num: Line counter.
 * Return: 0 if valid, -1 if not.
 */
int exe_cmd_with_path(char *f_path, char **toks, char *prog, int l_num)
	{
	pid_t pid;
	int status;

	if (access(f_path, X_OK) == -1)
	{
		fprintf(stderr, "%s: %d: %s: %s\n", prog, l_num,
				f_path, strerror(errno));
		return (-1);
	}
	pid = fork();
	if (pid == 0) /* Child */
	{
		if (execve(f_path, toks, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: %s\n", prog, l_num,
					f_path, strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0) /* If fork() fails */
	{
		perror(prog);
		return (-1);
	}
	else
	{
		do
			waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (0);
}
/**
 * direct_execute - Executes the command if it starts with '/' or '.'.
 * @tokens: The command and its arguments.
 * @prog: Program's name (argv[0]).
 * @l_num: Line counter.
 */
void direct_execute(char **tokens, char *prog, int l_num)
	{
	if (exe_cmd_with_path(tokens[0], tokens, prog, l_num) == -1)
		fprintf(stderr, "%s: %d: fork failed\n", prog, l_num);
}
/**
 * path_execute - Searches for cmd in PATH and executes it.
 * @tokens: The command and its arguments.
 * @prog: Program's name (argv[0]).
 * @l_num: Line counter.
 */
void path_execute(char **tokens, char *prog, int l_num)
	{
	path_t *path_list = parse_path();
	char *full_path = search_path(tokens[0], path_list);

	if (!path_list)
	{
		fprintf(stderr, "%s: %d: failed to parse PATH\n", prog, l_num);
		return;
	}
	if (full_path)
	{
		free(tokens[0]);  /* free the old command */
		tokens[0] = full_path;  /* replace with full path */

		if (exe_cmd_with_path(full_path, tokens, prog, l_num) == -1)
		{
			free_path_list(path_list);
			return;
		}
	}
	else
	{
		fprintf(stderr, "%s: %d: %s: command not found\n", prog,
				l_num, tokens[0]);
	}
	free_path_list(path_list);
}
/**
 * execute_command - Decides the method of command execution
 * @toks: Array of command and its arguments
 * @prog: Program's name (argv[0])
 * @l_num: Line counter
 */
void execute_command(char **toks, char *prog, int l_num)
{
	int i;

	if (toks[0] && strcmp(toks[0], "exit") == 0)
	{ /* Cleanup and exit */
		for (i = 0; toks[i]; i++)
			free(toks[i]);
		free(toks);
		exit(EXIT_SUCCESS);
	}
	/* If the command starts with '/' or '.', just execute directly */
	if (toks[0][0] == '/' || (toks[0][0] == '.' && toks[0][1] == '/'))
		direct_execute(toks, prog, l_num);
	else /* Otherwise, search for it in the PATH */
		path_execute(toks, prog, l_num);
}
