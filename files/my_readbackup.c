#include "my_blockchain.h"

int readbackup(int file_fd, struct blockchain* buffer)
{
	char* input;

	for (int j = 0; (input = my_readline(file_fd)); j++)
	{
		char** av = malloc(sizeof(char*) * 10);
		int ac = 0;

		av = sort_input(input, ',', &ac, av);

		for (int i = 0; i < ac; i++)
		{
			if (j == 0)
				add_node(av[i], buffer);
			else if (j == 1)
			{
				int x = i;
				remember_global_block(av[i], &x, buffer);
			}
			else
			{
				char tmp[30];
				my_itoa(tmp, buffer->nodes.values[j - 2]);
				add_block(av[i], tmp, buffer);
			}
		}

		free_arr(av, ac);
		free(input);
	}

	return 0;
}