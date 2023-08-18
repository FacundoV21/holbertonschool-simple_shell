#include "shell.h"
/**
* _getenv - retrieves the value of an environment variable
* @name: name of the environment variable to retrieve
* Return: pointer to the value of the environment variable,
* or NULL if not found
*/
char *_getenv(const char *name)
{
	int i = 0;
	int len = strlen(name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return (&environ[i][len + 1]);
		}
		i++;
	}
	return (NULL);
}
/**
 * print_env - Print the current environment variables
 *
 * Iterates through the global variable and prints
 * each string (environment variable) to stdout.
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
