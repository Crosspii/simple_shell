#include "shell.h"

/**
 * env_get - Retrieves the value of a specified environment variable.
 * @data: Structure containing shell-related arguments and data.
 * @name: The name of the environment variable to retrieve.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *env_get(data_t *data, const char *name)
{
	node_t *node = data->env;
	char *value_start;

	while (node)
	{
		value_start = str_starts(node->str, name);
		if (value_start && *value_start)
			return (value_start);
		node = node->next;
	}
	return (NULL);
}

/**
 * env_to_list - Populates a linked list with the current env variables.
 * @data: Structure containing shell-related arguments and data.
 *        Used to maintain a consistent function prototype.
 * Return: Always 0
 */
int env_to_list(data_t *data)
{
	node_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		list_append(&node, environ[i], 0);
	data->env = node;
	return (0);
}

/**
 * env_to_arr - Converts the environment linked list to an array of strings.
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: A string array of the environment variables.
 */
char **env_to_arr(data_t *data)
{
	if (!data->environ || data->env_modified)
	{
		data->environ = list_to_strs(data->env);
		data->env_modified = 0;
	}

	return (data->environ);
}

/**
 * env_remove - Removes an environment variable from the list.
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The environment variable to remove.
 *
 * Return: 1 if the variable was successfully removed, 0 otherwise.
 */
int env_remove(data_t *data, char *var)
{
	node_t *node = data->env;
	size_t i = 0;
	char *match;

	if (!node || !var)
		return (0);

	while (node)
	{
		match = str_starts(node->str, var);
		if (match && *match == '=')
		{
			data->env_modified = list_del_at(&(data->env), i);
			i = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->env_modified);
}

/**
 * env_init - Init a new environment variable or modifies an existing one.
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The environment variable name.
 * @value: The value to associate with the environment variable.
 *
 * Return: Always 0 on success.
 */
int env_init(data_t *data, char *var, char *value)
{
	char *buf = NULL;
	node_t *node;
	char *match;

	if (!var || !value)
		return (0);

	buf = malloc(str_len(var) + str_len(value) + 2);
	if (!buf)
		return (1);
	str_cpy(buf, var);
	str_cat(buf, "=");
	str_cat(buf, value);
	node = data->env;
	while (node)
	{
		match = str_starts(node->str, var);
		if (match && *match == '=')
		{
			free(node->str);
			node->str = buf;
			data->env_modified = 1;
			return (0);
		}
		node = node->next;
	}
	list_append(&(data->env), buf, 0);
	free(buf);
	data->env_modified = 1;
	return (0);
}
