#include "shell.h"

/**
 * is_chain_delim - checks if the current character in buffer is a chain delimiter
 * @data: the parameter structure
 * @buf: the character buffer
 * @pos: address of the current position in the buffer
 *
 * Return: 1 if a chain delimiter is found, 0 otherwise
 */
int is_chain_delim(data_t *data, char *buf, size_t *pos)
{
	size_t j = *pos;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		data->chain_type = OR_CMD;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		data->chain_type = AND_CMD;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		data->chain_type = CHAIN_CMD;
	}
	else
		return (0);
	*pos = j;
	return (1);
}

/**
 * chain_continue - determines if chaining should continue based on the last status
 * @data: the parameter structure
 * @buf: the character buffer
 * @pos: address of the current position in the buffer
 * @i: starting position in the buffer
 * @len: length of the buffer
 *
 * Return: Nothing
 */
void chain_continue(data_t *data, char *buf, size_t *pos, size_t i, size_t len)
{
	size_t j = *pos;

	if (data->chain_type == AND_CMD)
	{
		if (data->last_status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (data->chain_type == OR_CMD)
	{
		if (!data->last_status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*pos = j;
}
