#include "shell.h"
/**
 * exe_cmd_with_path - Executes a command given its full path
 * @f_path: The full path of the command
 * @toks: The command and its arguments
 * @prog: Program's name (argv[0])
 * @l_num: Line counter
 * Return: 0 if valid, -1 if not
 */
int exe_cmd_with_path(char *f_path, char **toks, char *prog, int l_num)
	{
	pid_t pid;
	int status;

	if (access(f_path, X_OK) == -1)
	{
		fprintf(stderr, "%s: %d: %s: %s\n", prog, l_num,
				f_path, strerror(errno));
		return (2);
	}
	pid = fork();
	if (pid == 0) /* Child */
	{
		if (execve(f_path, toks, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: %s\n", prog, l_num,
					f_path, strerror(errno));
			exit(errno);
		}
	}
	else if (pid < 0) /* If fork() fails */
	{
		perror(prog);
		return (2);
	}
	else
	{
		do
			waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}
/**
 * direct_execute - Executes the command if it starts with '/' or '.'
 * @tokens: The command and its arguments
 * @prog: Program's name (argv[0])
 * @l_num: Line counter
 * Return: Status of command execution
 */
int direct_execute(char **tokens, char *prog, int l_num)
{
	if (tokens[0][0] == '/' ||
		tokens[0][0] == '.' ||
		strncmp(tokens[0], "./", 2) == 0 ||
		strncmp(tokens[0], "../", 3) == 0 ||
		strncmp(tokens[0], "../../", 4) == 0)
	{
		return (exe_cmd_with_path(tokens[0], tokens, prog, l_num));
	}
	return (127);
}
/**
 * path_execute - Searches for cmd in PATH and executes it
 * @tokens: The command and its arguments
 * @prog: Program's name (argv[0])
 * @l_num: Line counter
 * Return: Status of command execution, -1 if error or command not found
 */
int path_execute(char **tokens, char *prog, int l_num)
{
	path_t *path_list = parse_path();
	char *f_path;
	int status;

	if (!path_list)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", prog, l_num, tokens[0]);
		return (127);
	}
	f_path = search_path(tokens[0], path_list);
	free_path_list(path_list);
	if (!f_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", prog, l_num, tokens[0]);
		return (127);
	}
	status = exe_cmd_with_path(f_path, tokens, prog, l_num);
	free(f_path);
	return (status);
}
/**
 * execute_command - Decides the method of command execution
 * @toks: Array of command and its arguments
 * @prog: Program's name (argv[0])
 * @l_num: Line counter
 * Return: Exit status of the command
 */
int execute_command(char **toks, char *prog, int l_num)
{
	int exit_status = 0;

	if (!toks || !toks[0])
	{
		return (EXIT_FAILURE);
	}
	if (strcmp(toks[0], "exit") == 0)
	{ /* Cleanup and exit */
		free_tokens(toks);
		return (-1);
	}
	if (strcmp(toks[0], "env") == 0)
	{
		print_env();
		free_tokens(toks);
		return (EXIT_SUCCESS);
	}
	exit_status = direct_execute(toks, prog, l_num);
	if (exit_status == 127)
		exit_status = path_execute(toks, prog, l_num);
	return (exit_status);
}
