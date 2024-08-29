#include "shell.h"

/**
 * list_get_index - finds the index of a specific node in the list
 * @head: pointer to the first node in the list
 * @node: pointer to the node whose index is needed
 *
 * Return: index of the target node, or -1 if not found
 */
ssize_t list_get_index(node_t *head, node_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * list_print_strs - outputs the string content of each node in the linked list
 * @head: pointer to the first node in the list
 *
 * Return: total count of nodes in the list
 */
size_t list_print_strs(const node_t *head)
{
	size_t count = 0;

	while (head)
	{
		print_str(head->str ? head->str : "(nil)");
		print_str("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * list_del_at - removes a node at a specified position in the list
 * @head: pointer to the address of the first node
 * @index: index of the node to be removed
 *
 * Return: 1 if successful, otherwise 0
 */
int list_del_at(node_t **head, unsigned int index)
{
	unsigned int i = 0;
	node_t *prev_node, *node;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * list_free - releases all the nodes in a linked list
 * @listhead: pointer to the address of the head node
 *
 * Return: void
 */
void list_free(node_t **listhead)
{
	node_t *head, *node, *next_node;

	if (!listhead || !*listhead)
		return;
	head = *listhead;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*listhead = NULL;
}
