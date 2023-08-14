#include "shell.h"
/**
 * main - The main loop of the shell
 * Return: Always 0 (success)
 */
int main(void)
{
    char *input_line = NULL;/* Ptr to hold user's input line */
    size_t len = 0; /* Size of the input buffer */
    ssize_t read; /* Number of characters read by getline */
	char **tokens;/*2D arr to hold each parsed tok frm inplin*/
	int i, fd_isatty; /* Loop counter for freeing memory */

    while (1)
    {/*Inf loop to keep shell running until manually closed */
        fd_isatty = isatty(STDIN_FILENO);
        if (fd_isatty)
            printf("#cisfun$ ");  /* Display prompt */
        read = getline(&input_line, &len, stdin);/*Read user inp. dynallocmem*/
        if (read == -1) /* If EOF (ctrl+d) */
        {
            free(input_line);
			printf("\n");
            exit(EXIT_SUCCESS);
        }
        tokens = parse_input(input_line); /* Parse inpline into tokens */
        if (tokens[0] == NULL)
        {
            free(tokens);
            continue;
        }
        if (tokens[0] && strcmp(tokens[0], "exit") == 0)
        { /* Cleanup and exit */
            for (i = 0; tokens[i]; i++)
                free(tokens[i]);
            free(tokens);
            free(input_line);
            exit(EXIT_SUCCESS);
        }
        execute_command(tokens); /* Execute user's cmd */
        for (i = 0; tokens[i]; i++) /* To avoid memory leaks */
            free(tokens[i]);
        free(tokens); /* Main tokens ptr */
        if(!fd_isatty)
            break;
    }
    free(input_line);/*To release mem if infloop ever breaks in fture mods*/
    return (EXIT_SUCCESS);/*This might not be reached due to infloop*/
}
