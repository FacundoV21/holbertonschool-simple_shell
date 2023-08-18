#include "shell.h"
/**
 * handle_sigint - Function to handle the SIGINT signal (Ctrl+C).
 * @sig: Signal number (not used)
 */
void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
	fflush(stdout);
}
/**
* main - The main loop of the shell.
* @argc: Argument acount.
* @argv: Array of argument strings.
* Return: Always 0 (success).
*/
int main(int argc, char **argv)
{
	char *input_line = NULL;/* Ptr to hold user's input line */
	size_t len = 0; /* Size of the input buffer */
	ssize_t read; /* Number of characters read by getline */
	char **tokens;/*2D arr to hold each parsed tok frm inplin*/
	int i, fd_isatty, line_counter = 0, exit_status = EXIT_SUCCESS;
	(void) argc;

	signal(SIGINT, handle_sigint);
	while (1)
	{/*Inf loop to keep shell running until manually closed */
		line_counter++;
		fd_isatty = isatty(STDIN_FILENO);
		if (fd_isatty)
			printf("#cisfun$ ");  /* Display prompt */
		read = getline(&input_line, &len, stdin);/*Read user inp. Dynallocmem*/
		if (read == -1) /* If EOF (ctrl+d) */
		{
			free(input_line);
			if (fd_isatty)
				printf("\n");
			return (exit_status);
		}
		tokens = parse_input(input_line); /* Parse inpline into tokens */
		if (tokens[0] == NULL)
		{
			free(tokens);
			continue;
		}
		exit_status = execute_command(tokens, argv[0], line_counter);
		for (i = 0; tokens[i]; i++) /* To avoid memory leaks */
			free(tokens[i]);
		free(tokens); /* Main tokens ptr */
		tokens = NULL;
		}
	free(input_line);/*To release mem if infloop ever breaks in fture mods*/
	return (exit_status);/*This might not be reached due to infloop*/
}
