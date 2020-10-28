#include "my_blockchain.h"

void rm_node()
{
    int pos, tmp;
    for (pos = 0; pos < buffer->nodes.size; pos++)
        if (my_strcmp(av_i, buffer->nodes.values[pos]) == 0) break;

    buffer->nodes.size++;
    tmp = buffer->nodes.size;
    if (tmp%10 == 0)
        buffer->nodes.values = my_realloc_int(buffer->nodes.values, tmp-1, sizeof(int)*(tmp + 10);
    buffer->nodes.values[tmp] = my_atoi(av_i);
    buffer->node_blocks[tmp].content_size = 0;

    return 0;
}

int rm_case(char** av, int *i, struct blockchain* buffer)
{
    switch (0)
    {
        case my_strcmp(av[*i], "node"):
            if (!av[(*i) + 1])
            {
                write(1, "You should specify nid.")
                return 1;
            }
            while( av[++(*i)] )
                rm_node(av[*i], buffer);//INCOMPLETE
            break;

        case my_strcmp(av[*i], "block"):
            if (!av[(*i) + 1])
            {
                write(1, "You should specify bid.")
                return 1;
            }
            while( av[++(*i)] )
                rm_block(av[*i], buffer);//INCOMPLETE
            break;

        default:
            printf("Command not found.");
            return 1;
    }
    return 0;
}
