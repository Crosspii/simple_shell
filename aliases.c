#include "shell.h"

/**
 * unset_alias - Removes an alias from the alias list.
 * @data: Structure containing shell-related arguments and data.
 * @str: The alias string to be removed.
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(data_t *data, char *str)
{
	int cb;
	char *p, temp_char;

	p = str_chr(str, '=');
	if (!p)
		return (1);
	temp_char = *p;
	*p = 0;
	cb = list_del_at(&(data->alias),
		list_get_index(data->alias, list_find_start(data->alias, str, -1)));
	*p = temp_char;
	return (cb);
}

/**
 * set_alias - Adds or updates an alias in the alias list.
 * @data: Structure containing shell-related arguments and data.
 * @str: The alias string to be set or updated.
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(data_t *data, char *str)
{
	char *eq_sign;

	eq_sign = str_chr(str, '=');
	if (!eq_sign)
		return (1);
	if (!*++eq_sign)
		return (unset_alias(data, str));

	unset_alias(data, str);
	return (list_append(&(data->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias in the format `alias='value'`.
 * @node: The node containing the alias information.
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(node_t *node)
{
	char *a = NULL, *eq_sign = NULL;

	if (node)
	{
		eq_sign = str_chr(node->str, '=');
		for (a = node->str; a <= eq_sign; a++)
			put_char(*a);
		put_char('\'');
		print_str(eq_sign + 1);
		print_str("'\n");
		return (0);
	}
	return (1);
}
