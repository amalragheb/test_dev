#include "shell.h"

/**
 * free_strings - frees a string
 * @pp: string of strings
 */
void free_strings(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * pfree - frees pointer
 * @ptr: address of pointer to be free
 *
 * Return: 1 if freed, or 0.
 */
int pfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * free_list - frees all nodes in the  list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(var_t **head_ptr)
{
	var_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
