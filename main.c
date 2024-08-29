#include "shell.h"

/**
 * main - Entry point of the shell program.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	data_t data[] = { INIT_DATA };
	int file_desc = 2;

	if (ac == 2)
	{
		file_desc = open_file(av[1]);
		if (file_desc == -1)
		{
			print_file_error(av);
			return (EXIT_FAILURE);
		}
		data->input_fd = file_desc;
	}

	initialize_shell(data);
	hsh(data, av);

    return (EXIT_SUCCESS);
}
