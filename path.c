#include "shell.h"
/**
* parse_path - Builds a linked list of directories from PATH
* Return: Pointer to the head of the linked list
* This function tokenises the PATH variable using : (delimiter)
* and stores each directory into a node in a singly linked list.
**/
path_t *parse_path(void)
{
	char *ori_path, *path = NULL, *token;
	path_t *head = NULL, *new_node;

	ori_path = _getenv("PATH");
	if (!ori_path || strlen(ori_path) == 0)
		return (NULL);
	path = strdup(ori_path);
	if (!path)
	{
		perror("shell: Error duplicating PATH");
		return (NULL);
	}
	token = strtok(path, ":");
	while (token)
	{
		new_node = create_new_node(token);
		if (!new_node)
		{
			free_path_list(head);
			free(path);
			exit(EXIT_FAILURE);
		}
		append_to_list(&head, new_node);
		token = strtok(NULL, ":");
	}
	free(path);
	return (head);
}
/**
* search_path - Searches for an executable in PATH directories
* @cmd: The command to find
* @path_list: The linked list of PATH directories
* Return: Full path to executable or NULL if not found
*
* This fn iterates through the linked list of directories,
* adding the provided cmd and checking if the returned full
* path is valid and executable.
**/
char *search_path(char *cmd, path_t *path_list)
{
	char full_path[PATH_MAX];
	struct stat st;

	while (path_list) /* Iterate through each dirtry in linked list*/
	{ /* Allocate memory for the full path of the command */
		sprintf(full_path, "%s/%s", path_list->dir, cmd);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
			return (strdup(full_path));
		else if (errno != ENOENT)
		{
			perror("shell: Error using stat");
			return (NULL);
		}
		path_list = path_list->next;
	}
	return (NULL);
}
/**
* create_new_node - Create a new node with given token data
* @token: token data for node
* Return: pointer to the new node
**/
path_t *create_new_node(char *token)
{
	path_t *new_node = malloc(sizeof(path_t));

	if (!new_node)
		return (NULL);
	new_node->dir = strdup(token);
	if (!new_node->dir)
	{
		free(new_node->dir);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}
/**
* append_to_list - Append the node to the list
* @head: pointer to head of the list
* @new_node: node to append
**/
void append_to_list(path_t **head, path_t *new_node)
{
	path_t *temp;

	if (!(*head))
	{
		*head = new_node;
		return;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}
/**
* free_path_list - Frees a linked list of PATH directories
* @head: The head of the linked list
* This function iteratively frees each node of the linked list
* starting from the head, ensuring that no memory is leaked.
**/
void free_path_list(path_t *head)
{
	path_t *temp;

	while (head)/*Iter through list, freeing each dir node*/
	{
		temp = head->next;
		free(head->dir); /* Freeing the directory string */
		free(head); /* Freeing the node itself */
		head = temp;
	}
}
