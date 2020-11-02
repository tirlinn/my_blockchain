#include "my_blockchain.h"

int ls_case(char* av_i, struct blockchain* buffer)
{
    if (my_strcmp(av_i, "-l") == 0)
    {
        if (list_blocks(buffer) == 1) return 1;
    }
    else
    {
        if (list_nodes(buffer) == 1) return 1;
    }

    return 0;
}

int list_blocks(struct blockchain* buffer)
{
    for (int i = 0; i < buffer->nodes.size; i++)
    {
        char tmp[18];
        my_itoa(tmp, buffer->nodes.values[i]);
        write(1, tmp, my_strlen(tmp));
        if (buffer->node_blocks[i].content_size != 0)
        {
            write(1, ": ", 2);
            for (int j = 0; j < buffer->node_blocks[i].content_size; j++)
            {
                write(1, buffer->node_blocks[i].content[j], my_strlen(buffer->node_blocks[i].content[j]));
                if (j != buffer->node_blocks[i].content_size - 1)
                    write(1, ", ", 2);
                else
                    write(1, ".", 1);
            }
        }
        write(1, "\n", 1);
    }
    return 0;
}

int list_nodes(struct blockchain* buffer)
{
    for (int i = 0; i < buffer->nodes.size; i++)
    {
        char tmp[18];
        my_itoa(tmp, buffer->nodes.values[i]);
        write(1, tmp, my_strlen(tmp));
        write(1, "\n", 1);
    }
    return 0;
}