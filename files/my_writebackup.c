#include "my_blockchain.h"

int writebackup(int file_fd, struct blockchain buffer)
{
	char tmp[1000];
	int i;

	for (i = 0; i < buffer.nodes.size; i++)
	{
		char tmp2[18];
		my_itoa(tmp2, buffer.nodes.values[i]);
		if (i == 0)
		{
			my_strcpy(tmp, tmp2);
		}
		else
		{
			my_strcat(tmp, ",");
			my_strcat(tmp, tmp2);
		}
	}

	if (i == 0)
		write(file_fd, "\n", 1);
	else
	{
		my_strcat(tmp, "\n");
		write(file_fd, tmp, my_strlen(tmp));
	}

	for (i = 0; i < buffer.blocks.size; i++)
	{
		if (i == 0)
		{
			my_strcpy(tmp, buffer.blocks.list[i]);
		}
		else
		{
			my_strcat(tmp, ",");
			my_strcat(tmp, buffer.blocks.list[i]);
		}
	}

	if (i == 0)
		write(file_fd, "\n", 1);
	else
	{
		my_strcat(tmp, "\n");
		write(file_fd, tmp, my_strlen(tmp));
	}

	for (i = 0; i < buffer.nodes.size; i++)
	{
		int j;
		for (j = 0; j < buffer.node_blocks[i].content_size; j++)
		{
			if (j == 0)
			{
				my_strcpy(tmp, buffer.node_blocks[i].content[j]);
			}
			else
			{
				my_strcat(tmp, ",");
				my_strcat(tmp, buffer.node_blocks[i].content[j]);
			}
		}

		if (j == 0)
			write(file_fd, "\n", 1);
		else
		{
			my_strcat(tmp, "\n");
			write(file_fd, tmp, my_strlen(tmp));
		}
	}

	return 0;
}