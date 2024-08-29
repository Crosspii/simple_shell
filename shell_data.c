#include "shell.h"

/**
 * clear_data - Resets the fields of the data_t structure.
 * @data: Pointer to the data_t structure to be reset.
 */
void clear_data(data_t *data)
{
	data->input = NULL;
	data->args = NULL;
	data->exec_path = NULL;
	data->arg_count = 0;
}

/**
 * set_data - Initializes the fields of the data_t structure based on input.
 * @data: Pointer to the data_t structure to be initialized.
 * @av: Array of command-line arguments (argument vector).
 */
void set_data(data_t *data, char **av)
{
	int i = 0;

	data->file_name = av[0];
	if (data->input)
	{
		data->args = split_str(data->input, " \t");
		if (!data->args)
		{

			data->args = malloc(sizeof(char *) * 2);
			if (data->args)
			{
				data->args[0] = str_dup(data->input);
				data->args[1] = NULL;
			}
		}
		for (i = 0; data->args && data->args[i]; i++)
			;
		data->arg_count = i;

		expand_alias(data);
		expand_var(data);
	}
}

/**
 * free_data - Frees the fields of the data_t structure.
 * @data: Pointer to the data_t structure to be freed.
 * @all: Flag indicating whether to free all fields.
 */
void free_data(data_t *data, int all)
{
	free_arr(data->args);
	data->args = NULL;
	data->exec_path = NULL;
	if (all)
	{
		if (!data->chain_buf)
			free(data->input);
		if (data->env)
			list_free(&(data->env));
		if (data->hist)
			list_free(&(data->hist));
		if (data->alias)
			list_free(&(data->alias));
		free_arr(data->environ);
			data->environ = NULL;
		free_ptr((void **)data->chain_buf);
		if (data->input_fd > 2)
			close(data->input_fd);
		put_char(BUF_FLUSH);
	}
}
