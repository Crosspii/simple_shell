#include "shell.h"

/**
 * expand_alias - replaces aliases in the tokenized string
 * @data: the parameter structure
 *
 * Return: 1 if an alias was replaced, else 0
 */
int expand_alias(data_t *data)
{
	int i;
	char *p;
	node_t *node;

	for (i = 0; i < 10; i++)
	{
		node = list_find_start(data->alias, data->args[0], '=');
		if (!node)
			return (0);
		free(data->args[0]);
		p = str_chr(node->str, '=');
		if (!p)
			return (0);
		p = str_dup(p + 1);
		if (!p)
			return (0);
		data->args[0] = p;
	}
	return (1);
}

/**
 * expand_var - replaces variables in the tokenized string
 * @data: the parameter structure
 *
 * Return: 1 if a variable was replaced, else 0
 */
int expand_var(data_t *data)
{
	int i = 0;
	node_t *node;

	for (i = 0; data->args[i]; i++)
	{
		if (data->args[i][0] != '$' || !data->args[i][1])
			continue;

		if (!str_cmp(data->args[i], "$?"))
		{
			expand_str(&(data->args[i]),
				str_dup(int_to_string(data->last_status, 10, 0)));
			continue;
		}
		if (!str_cmp(data->args[i], "$$"))
		{
			expand_str(&(data->args[i]),
				str_dup(int_to_string(getpid(), 10, 0)));
			continue;
		}
		node = list_find_start(data->env, &data->args[i][1], '=');
		if (node)
		{
			expand_str(&(data->args[i]),
				str_dup(str_chr(node->str, '=') + 1));
			continue;
		}
		expand_str(&data->args[i], str_dup(""));

	}
	return (0);
}

/**
 * expand_str - replaces a string with a new value
 * @oldstr: address of the old string
 * @newstr: new string to replace the old string
 *
 * Return: 1 if the replacement was successful, 0 otherwise
 */
int expand_str(char **oldstr, char *newstr)
{
	free(*oldstr);
	*oldstr = newstr;
	return (1);
}
