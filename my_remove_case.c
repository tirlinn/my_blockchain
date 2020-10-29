#include "my_blockchain.h"

int rm_node(char* av_i, struct blockchain *buffer)
{
    int tmp;
    int input;
    int pos;

    if ( (input = my_atoi(av_i)) < 0)
    {
        write(1, "Error.\n", my_strlen("Error.\n"));
        return 1;
    }

    for (pos = 0; pos < buffer->nodes.size; pos++)
        if (input == buffer->nodes.values[pos]) break;
    if (pos == buffer->nodes.size)
    {
        write(1, "Node doesn't exist", my_strlen("Node doesn't exist"));
        return 1;
    }

    for (int i = 0; i < buffer->node_blocks[pos].content_size; i++)
        buffer->node_blocks[pos].content[i][0] = '\0';
    buffer->node_blocks[pos].content_size = 0;

    for ( ; pos < buffer->nodes.size; pos++)
        buffer->nodes.values[pos] = buffer->nodes.values[pos + 1];
    // buffer->nodes.values[buffer->pos] = 0;
    buffer->nodes.size--;

    char temporary[16]; //REMOVE
    for (int i = 0; i < buffer->nodes.size; i++)
    {
        my_itoa(temporary, buffer->nodes.values[i]); //REMOVE
        write(1, temporary, my_strlen(temporary)); //REMOVE
    }

    write(1, "Successfully removed node.\n", my_strlen("Successfully added node.\n"));
    return 0;
}

int rm_block()
{
    
}

int rm_case(char** av, int ac, int *i, struct blockchain* buffer)
{
    if (my_strcmp(av[*i], "node") == 0)
    {
        if (ac == 2)
        {
            write(1, "You should specify nid.")
            return 1;
        }
        else if (rm_node(av[++(*i)], buffer)) == 1)
            return 1;
        char tmp[16]; //REMOVE
        my_itoa(tmp, buffer->nodes.values[0]); //REMOVE
        write(1, tmp, my_strlen(tmp)); //REMOVE
    }
    else if (my_strcmp(av[*i], "block") == 0)
        if (ac == 2)
        {
            write(1, "You should specify bid.")
            return 1;
        }
        else if (rm_block(av[++(*i)], buffer)) == 1)
            return 1;
        char tmp[16]; //REMOVE
        my_itoa(tmp, buffer->nodes.values[0]); //REMOVE
        write(1, tmp, my_strlen(tmp)); //REMOVE
    else
    {
        write(1, "Command not found.\n", my_strlen("Command not found.\n"));
        return 1;
    }

    return 0;
}