#include "shell.h"

/**
 * list_append - appends a new element to the end of the linked list
 * @head: pointer to the address of the head node
 * @str: string value to be stored in the new node
 * @num: index used for tracking purposes, such as history
 *
 * Return: pointer to the newly added node
 */
node_t *list_append(node_t **head, const char *str, int num)
{
	node_t *node, *new_node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(node_t));
	if (!new_node)
		return (NULL);
	mem_set((void *)new_node, 0, sizeof(node_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = str_dup(str);
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
 * list_size - calculates the number of nodes in a linked list
 * @head: pointer to the first node in the list
 *
 * Return: total number of nodes in the list
 */
size_t list_size(const node_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * list_to_strs - converts a linked list into an array of strings
 * @head: pointer to the head of the list
 *
 * Return: array of strings from the list
 */
char **list_to_strs(node_t *head)
{
	node_t *node = head;
	size_t i = list_size(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = str_cpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * list_print - displays all elements of a linked list
 * @h: pointer to the first node in the list
 *
 * Return: total number of nodes printed
 */
size_t list_print(const node_t *h)
{
	size_t count = 0;

	while (h)
	{
		print_str(int_to_string(h->num, 10, 0));
		put_char(':');
		put_char(' ');
		print_str(h->str ? h->str : "(nil)");
		print_str("\n");
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * list_find_start - finds the first node with a string that starts with a prefix
 * @node: pointer to the start of the list
 * @prefix: string prefix to look for
 * @c: character that should follow the prefix, or -1 if not needed
 *
 * Return: pointer to the matching node, or NULL if no match
 */
node_t *list_find_start(node_t *node, char *prefix, char c)
{
	char *matched_str = NULL;

	while (node)
	{
		matched_str = str_starts(node->str, prefix);
		if (matched_str && ((c == -1) || (*matched_str == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
