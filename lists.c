#include "shell.h"

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
var_t *add_node_end(var_t **head, const char *str, int num)
{
    var_t *new_node, *node;

    if (!head)
        return (NULL);

    node = *head;
    new_node = malloc(sizeof(var_t));
    if (!new_node)
        return (NULL);
    _memset((void *)new_node, 0, sizeof(var_t));
    new_node->num = num;
    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }
    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *head = new_node;
    return (new_node);
}

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const var_t *h)
{
    size_t i = 0;

    while (h)
    {
        h = h->next;
        i++;
    }
    return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(var_t *head)
{
    var_t *node = head;
    size_t i = list_len(head), j;
    char **strs;
    char *str;

    if (!head || !i)
        return (NULL);
    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return (NULL);
    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(_strlen(node->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return (NULL);
        }

        str = _strcpy(str, node->str);
        strs[i] = str;
    }
    strs[i] = NULL;
    return (strs);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
var_t *node_starts_with(var_t *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = starts_with(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return (node);
        node = node->next;
    }
    return (NULL);
}
