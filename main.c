#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	data_t data[] = { INIT_DATA };
	int file_desc = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_desc)
		: "r" (file_desc));

	if (ac == 2)
	{
		file_desc = open(av[1], O_RDONLY);
		if (file_desc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_to_stderr(av[0]);
				print_to_stderr(": 0: Can't open ");
				print_to_stderr(av[1]);
				print_char_stderr('\n');
				print_char_stderr(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->input_fd = file_desc;
	}
	env_to_list(data);
	hist_read(data);
	hsh(data, av);
	return (EXIT_SUCCESS);
}
