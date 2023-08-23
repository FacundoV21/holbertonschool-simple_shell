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
	char **tokens;/*2D arr to hold each parsed tok from input line*/
	int fd_isatty, line_counter = 0, exit_status = EXIT_SUCCESS;
	(void) argc;

	signal(SIGINT, handle_sigint);
	while (1) /*Inf loop to keep shell running until manually closed */
	{
		line_counter++;
		fd_isatty = isatty(STDIN_FILENO);
		if (fd_isatty)
			printf("#cisfun$ ");  /* Display prompt */
		read = getline(&input_line, &len, stdin);/*Read user inp. Dynallocmem*/
		if (read == -1) /* EOF (ctrl+d) detected */
		{
			printf("\n");
			free(input_line);
			exit(exit_status);
		}
			break;
		tokens = parse_input(input_line); /* Parse input line into tokens */
		if (!tokens || !tokens[0])/*If toks aren't present,free mem and cont*/
		{
			free(tokens);
			continue;
		}
		exit_status = execute_command(tokens, argv[0], line_counter);
		free_tokens(tokens); /* Main tokens ptr */
	}
	/*Clean and release mem if inf loop ever breaks due to fture modfcations*/
	return (cleanup(input_line, exit_status, fd_isatty));
}
/**
 * cleanup - Frees memory and handles end of program cleanup.
 * @input_line: The user input line.
 * @status: The exit status to return.
 * @fd_isatty: Boolean indicating if input is from a terminal.
 */
int cleanup(char *input_line, int status, int fd_isatty)
{
	free(input_line);
	if (fd_isatty)
		printf("\n");
	return (status);
}
/**
 * free_tokens - Frees the tokens allocated in parse_input.
 * @tokens: The array of token strings.
 */
void free_tokens(char **tokens)
{
	int i;

	for (i = 0; tokens[i]; i++)
		free(tokens[i]);
	free(tokens);
}
