#include "shell.h"

/**
 * hist_create - Creates or overwrites the history file with current history.
 * @data: Pointer to the data_t structure containing relevant data.
 *
 * Return: 1 on success, -1 on failure.
 */
int hist_create(data_t *data)
{
	ssize_t fd;
	char *filename = hist_file(data);
	node_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = data->hist; node; node = node->next)
	{
		write_str_fd(node->str, fd);
		write_char_fd('\n', fd);
	}
	write_char_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * hist_file - Constructs the path to the history file.
 * @data: Pointer to the data_t structure containing relevant data.
 *
 * Return: Pointer to an allocated string containing the history file path.
 */
char *hist_file(data_t *data)
{
	char *buf, *dir;

	dir = env_get(data, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (str_len(dir) + str_len(HISTORY_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	str_cpy(buf, dir);
	str_cat(buf, "/");
	str_cat(buf, HISTORY_FILE);
	return (buf);
}

/**
 * hist_adds_entry - Adds a history entry to the history linked list.
 * @data: Pointer to the data_t structure containing relevant data.
 * @buf: Buffer containing the history entry.
 * @linecount: Line number of the history entry.
 *
 * Return: Always 0.
 */
int hist_adds_entry(data_t *data, char *buf, int linecount)
{
	node_t *node = NULL;

	if (data->hist)
		node = data->hist;
	list_append(&node, buf, linecount);

	if (!data->hist)
		data->hist = node;
	return (0);
}

/**
 * hist_adjust - Renumbers the history linked list entries.
 * @data: Pointer to the data_t structure containing relevant data.
 *
 * Return: The new history count.
 */
int hist_adjust(data_t *data)
{
	node_t *node = data->hist;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (data->hist_num = i);
}

/**
 * hist_read - Reads history from the file into the history linked list.
 * @data: Pointer to the data_t structure containing relevant data.
 *
 * Return: Number of hist_num on success, 0 on failure.
 */
int hist_read(data_t *data)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = hist_file(data);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			hist_adds_entry(data, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		hist_adds_entry(data, buf + last, linecount++);
	free(buf);
	data->hist_num = linecount;
	while (data->hist_num-- >= MAX_HIST_COUNT)
		list_del_at(&(data->hist), 0);
	hist_adjust(data);
	return (data->hist_num);
}
