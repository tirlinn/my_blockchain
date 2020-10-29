#include "my_blockchain.h"

int add_node(char* av_i, struct blockchain *buffer)
{
    int tmp;
    int input;
    if ( (input = my_atoi(av_i)) < 0)
    {
        write(1, "Error.\n", my_strlen("Error.\n"));
        return 1;
    }

    for (int i = 0; i < buffer->nodes.size; i++)
        if (input == buffer->nodes.values[i])
        {
            write(1, "This node already exists.\n", my_strlen("This node already exists.\n"));
            return 1;
        }

    tmp = buffer->nodes.size;
    if (tmp % 10 == 0)
    {
        buffer->nodes.values = my_realloc_int(buffer->nodes.values, tmp, sizeof(int)*(tmp + 10));
        buffer->node_blocks = my_realloc_struct(buffer->node_blocks, tmp, sizeof(struct s_node_blocks) *(tmp + 10));
        for (int i = tmp; i < tmp + 10; i++)
            buffer->node_blocks[tmp].content = malloc(sizeof(char*) * 10);
    }
    buffer->nodes.values[tmp] = input;
    buffer->node_blocks[tmp].content_size = 0;
    buffer->nodes.size++;

    write(1, "Successfully added node.\n", my_strlen("Successfully added node.\n"));

    return 0;
}

void remember_block(char* av_b, struct blockchain *buffer)
{
    int i;

    for(i = 0; i < buffer->blocks.size; i++)
        if (my_strcmp(av_b, buffer->blocks.list[i]) == 0) 
            break;

    if (i == buffer->blocks.size)
    {
        int tmp = buffer->blocks.size;
        if(tmp % 10 == 0)
            buffer->blocks.list = my_realloc_arr(buffer->blocks.list, tmp - 1, sizeof(char*) * (tmp + 10));
        buffer->blocks.list[tmp] = malloc(sizeof(char) * (my_strlen(av_b) + 1));
        my_strcpy(buffer->blocks.list[tmp], av_b);
        buffer->blocks.size++;
        write(1, "Successfully remembered block.\n", my_strlen("Successfully remembered block.\n"));
    }
}

int add_block(char* av_b, char* av_i, struct blockchain *buffer)
{
    int pos;
    int input;
    if ( (input = my_atoi(av_i)) < 0)
    {
        write(1, "Error.\n", my_strlen("Error.\n"));
        return 1;
    }
    //find position of the node in struct nodes.
    for (pos = 0; pos < buffer->nodes.size; pos++)
        if (input == buffer->nodes.values[pos])  break;
    // check if the node already exists
    if (pos == buffer->nodes.size)
    {
        write(1, "Node doesn't exist.\n", my_strlen("Node doesn't exist.\n"));
        return 1;
    }
    //check if the block already exists
    for (int j = 0; j < buffer->node_blocks[pos].content_size; j++)
        if (my_strcmp(av_b, buffer->node_blocks[pos].content[j]) == 0)
        {
            write(1, "This block already exists.\n", my_strlen("This block already exists.\n"));
            return 1;
        }
    // add new block to struct blocks if it doesn't exis
    remember_block(av_b, buffer);
    //add block to the node
    if(pos % 10 == 0)
        buffer->node_blocks[pos].content = my_realloc_arr(buffer->node_blocks[pos].content, pos - 1, sizeof(char*) * (pos + 10));
    buffer->node_blocks[pos].content[pos] = malloc(sizeof(char)*(my_strlen(av_b) + 1));
    my_strcpy(buffer->node_blocks[pos].content[pos], av_b);
    buffer->node_blocks[pos].content_size++;

    write(1, "Successfully added block.\n", my_strlen("Successfully added block.\n"));

    return 0;
}

int add_case (char** av, int ac, int *i, struct blockchain* buffer)
{
    if (my_strcmp(av[*i], "node") == 0)
    {
        if (ac == 2)
        {
            write(1, "You should specify nid.\n", my_strlen("You should specify nid.\n"));
            return 1;
        }
        else if (add_node(av[++(*i)], buffer) == 1)
            return 1;
        
    }
    else if (my_strcmp(av[*i], "block") == 0)
    {
        if (ac == 2)
        {
            write(1, "You should specify bid.\n", my_strlen("You should specify bid.\n"));
            return 1;
        }
        else if (ac == 3)
        {
            write(1, "You should specify nid.\n", my_strlen("You should specify nid.\n"));
            return 1;
        }
        else
            *i = 3;
        while(*i < ac)
            if (add_block(av[2], av[(*i)++], buffer) == 1) return 1;
    }
    else
    {
        write(1, "Command not found.\n", my_strlen("Command not found.\n"));
        return 1;
    }

    return 0;
}
