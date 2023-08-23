#include "shell.h"

/**
* parse_input - Tokenises the input line
* @input: The input line
* Return: Array of tokens
*/
char **parse_input(char *input)
{
	char **tokens;
	size_t bufsize = BUFFER_SIZE, position = 0;
	char *token;
	char *delim = " \t\n";
	char end_char, *end;

	input[strcspn(input, "\n\r")] = '\0';
	token = strtok(input, delim);
	tokens = (token) ? malloc(bufsize * sizeof(char *)) : init_token();
	check_allocation(tokens);

	while (token)
	{
		if (token[0] == '\"' || token[0] == '\'')
		{
			end_char = token[0] == '\"' ? '\"' : '\'';
			token++;
			end = strchr(token, end_char);
			if (end)
			{
				*end = '\0';
			}
		}
		else if (token[0] == '\\')
		{
			token++;
		}
		tokens[position++] = strdup(token);
		if (position >= bufsize)
			tokens = resize_token_buffer(tokens, &bufsize);
		token = strtok(NULL, delim);
	}
	if (tokens)
		tokens[position] = NULL;
	return (tokens);
}
/**
* init_token - Initialize a token
* Return: Initialized token
*/
char **init_token(void)
{
	char **tokens;

	tokens = malloc(sizeof(char *));
	if (!tokens)
	{
		fprintf(stderr, "shell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	tokens[0] = NULL;
	return (tokens);
}
/**
* check_allocation - Checks memory allocation
* @tokens: The allocated memory
*/
void check_allocation(char **tokens)
{
	if (!tokens)
	{
		fprintf(stderr, "shell: allocation error\n");
		exit(EXIT_FAILURE);
	}
}
/**
* resize_token_buffer - Resizes the token buffer
* @tokens: The token buffer
* @bufsize: The buffer size
* Return: The resized buffer
*/
char **resize_token_buffer(char **tokens, size_t *bufsize)
{
	size_t new_bufsize = *bufsize + BUFFER_SIZE;
	char **new_tokens = malloc(new_bufsize * sizeof(char *));
	size_t i;

	if (!new_tokens)
	{
		free(tokens);
		check_allocation(new_tokens);
	}
	for (i = 0; i < *bufsize; i++)
		new_tokens[i] = tokens[i];
	free(tokens);
	*bufsize = new_bufsize;
	return (new_tokens);
}
