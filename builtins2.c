#include "shell.h"

/**
 * b_alias - Handles alias in the shell, akin to the alias built-in cmd.
 * @data: Structure containing shell-related arguments and data.
 *        Used to maintain a consistent function prototype.
 * Return: Always 0
 */
int b_alias(data_t *data)
{
	int i = 0;
	char *eq_sign = NULL;
	node_t *node = NULL;

	if (data->arg_count == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->args[i]; i++)
	{
		eq_sign = str_chr(data->args[i], '=');
		if (eq_sign)
			set_alias(data, data->args[i]);
		else
			print_alias(list_find_start(data->alias, data->args[i], '='));
	}

	return (0);
}

/**
 * b_env - Displays the current environment variables.
 * @data: Structure containing shell-related arguments and data.
 *        Used to maintain a consistent function prototype.
 * Return: Always 0
 */
int b_env(data_t *data)
{
	list_print_strs(data->env);
	return (0);
}

/**
 * b_setenv - Init a new environment variable or modifies an existing one.
 * @data: Structure containing shell-related arguments and data.
 *        Used to maintain a consistent function prototype.
 * Return: 0 on success, 1 if incorrect number of arguments are provided.
 */
int b_setenv(data_t *data)
{
	if (data->arg_count != 3)
	{
		print_to_stderr("Incorrect number of arguements\n");
		return (1);
	}
	if (env_init(data, data->args[1], data->args[2]))
		return (0);
	return (1);
}

/**
 * b_unsetenv - Removes an environment variable.
 * @data: Structure containing shell-related arguments and data.
 *        Used to maintain a consistent function prototype.
 * Return: 0 on success, 1 if too few arguments are provided.
 */
int b_unsetenv(data_t *data)
{
	int i;

	if (data->arg_count == 1)
	{
		print_to_stderr("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= data->arg_count; i++)
		env_remove(data, data->args[i]);

	return (0);
}
