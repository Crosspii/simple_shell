#include "shell.h"

/**
 * input_buf - Buffers chained commands from the input.
 * @data: Pointer to the data_t structure containing relevant data.
 * @buf: Address of the pointer to the buffer.
 * @len: Address of the length variable.
 *
 * Return: Number of bytes read from input.
 */
ssize_t input_buf(data_t *data, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sig_handler);
		r = input_next_line(data, buf, &len_p);
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			data->line_flag = 1;
			rm_comments(*buf);
			hist_adds_entry(data, *buf, data->hist_num++);
			*len = r;
			data->chain_buf = buf;
		}
	}
	return (r);
}

/**
 * input_get_line - Retrieves a line of input, excluding the newline character.
 * @data: Pointer to the data_t structure containing relevant data.
 *
 * Return: Number of bytes read from input.
 */
ssize_t input_get_line(data_t *data)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(data->input), *p;

	put_char(BUF_FLUSH);
	r = input_buf(data, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		chain_continue(data, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain_delim(data, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			data->chain_type = NORM_CMD;
		}

		*buf_p = p;
		return (str_len(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - Reads data into a buffer.
 * @data: Pointer to the data_t structure containing relevant data.
 * @buf: Buffer to read data into.
 * @i: Size of data read.
 *
 * Return: Number of bytes read.
 */
ssize_t read_buf(data_t *data, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(data->input_fd, buf, BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * input_next_line - Reads the next line of input from STDIN.
 * @data: Pointer to the data_t structure containing relevant data.
 * @ptr: Address of the pointer to the buffer, preallocated or NULL.
 * @length: Size of the preallocated buffer if not NULL.
 *
 * Return: Number of bytes read.
 */
int input_next_line(data_t *data, char **ptr, size_t *length)
{
	static char buf[BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(data, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = str_chr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = mem_realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		str_ncat(new_p, buf + i, k - i);
	else
		str_ncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sig_handler - Handles SIGINT (Ctrl-C) signal by printing a newline 
 *               and prompt, then flushing the output.
 * @sig_num: The signal number (unused).
 *
 * Return: Nothing.
 */
void sig_handler(__attribute__((unused))int sig_num)
{
	print_str("\n");
	print_str("$ ");
	put_char(BUF_FLUSH);
}
