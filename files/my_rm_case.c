#include "my_blockchain.h"

bool find_node_pos(int* pos, int input, struct blockchain* buffer)
{
    for (*pos = 0; *pos < buffer->nodes.size; (*pos)++)
        if (input == buffer->nodes.values[*pos]) break;

    if (*pos == buffer->nodes.size) return false;

    return true;
}

bool block_unique(int pos, char* str, struct blockchain* buffer)
{
    for (int j = 0; j != pos && j < buffer->nodes.size; j++)
        for (int k = 0; k < buffer->node_blocks[j].content_size; k++)
            if (strcmp(str, buffer->node_blocks[j].content[k]) == 0)
                return false;
    return true;
}

void forget_the_node_blocks(int pos, struct blockchain* buffer)
{
    for (int i = 0; i < buffer->node_blocks[pos].content_size; i++)
    {
        if (block_unique(pos, buffer->node_blocks[pos].content[i], buffer))
            forget_global_block(buffer->node_blocks[pos].content[i], buffer);
        free(buffer->node_blocks[pos].content[i]);
    }
    buffer->node_blocks[pos].content_size = 0;
}

void forget_the_node(int pos, struct blockchain* buffer)
{
    for (; pos < buffer->nodes.size - 1; pos++)
        buffer->nodes.values[pos] = buffer->nodes.values[pos + 1];
    buffer->nodes.size--;
    buffer->nodes.values[pos] = 0;

    if (pos % 10 == 0 && pos != 0)
    {
        buffer->nodes.values = my_realloc_int(buffer->nodes.values, (pos + 10), sizeof(int) * pos);
        buffer->node_blocks = my_realloc_struct(buffer->node_blocks, (pos + 10), sizeof(struct s_node_blocks) * pos);
        for (int i = 0; i < 10; i++)
            buffer->node_blocks[pos + i].content_size = 0;
    }
}

int rm_node(char* av_i, struct blockchain* buffer)
{
    int input = 0;
    int pos = 0;

    if ((input = my_atoi(av_i)) < 0)
    {
        write(1, "Error.\n", my_strlen("Error.\n"));
        return 1;
    }

    if (!find_node_pos(&pos, input, buffer))
    {
        write(1, "Node doesn't exist\n", my_strlen("Node doesn't exist\n"));
        return 1;
    }

    forget_the_node_blocks(pos, buffer);

    forget_the_node(pos, buffer);

    char temporary[18];
    for (int i = 0; i < buffer->nodes.size; i++)
    {
        my_itoa(temporary, buffer->nodes.values[i]); //REMOVE
        write(1, temporary, my_strlen(temporary)); //REMOVE
    }

    write(1, "Successfully removed node.\n", my_strlen("Successfully removed node.\n"));

    return 0;
}

bool find_global_block(char* av_b, int* pos, struct blockchain* buffer)
{
    for (*pos = 0; *pos < buffer->blocks.size; (*pos)++)
        if (my_strcmp(av_b, buffer->blocks.list[*pos]) == 0) break;

    if (*pos == buffer->blocks.size)
        return false;

    return true;
}

int forget_global_block(char* av_b, struct blockchain* buffer)
{
    int pos;

    if (!find_global_block(av_b, &pos, buffer))
    {
        write(1, "This block doesn't exist.", my_strlen("This block doesn't exist."));
        return 1;
    }

    free(buffer->blocks.list[pos]);
    for (; pos < buffer->blocks.size - 1; pos++)
        buffer->blocks.list[pos] = buffer->blocks.list[pos + 1];
    buffer->blocks.list[pos] = 0;
    buffer->blocks.size--;

    if (pos != 0 && pos % 10 == 0)
        buffer->blocks.list = my_realloc_arr(buffer->blocks.list, pos + 10, sizeof(char*) * (pos));

    write(1, "Successfully forgot block.\n", my_strlen("Successfully forgot block.\n"));
    return 0;
}

void forget_the_block_in_node(char *av_b, int i, struct blockchain* buffer)
{
    for (int j = 0; j < buffer->node_blocks[i].content_size; j++)
        if (my_strcmp(av_b, buffer->node_blocks[i].content[j]) == 0)
        {
            free(buffer->node_blocks[i].content[j]);
            for (; j < buffer->node_blocks[i].content_size - 1; j++)
                buffer->node_blocks[i].content[j] = buffer->node_blocks[i].content[j + 1];
            buffer->node_blocks[i].content[j] = 0;
            buffer->node_blocks[i].content_size--;
            int tmp = buffer->node_blocks[i].content_size;
            if (tmp != 0 && tmp % 10 == 0)
                buffer->node_blocks[i].content = my_realloc_arr(buffer->node_blocks[i].content, tmp + 10, sizeof(char*) * (tmp));
        }
}

int rm_block(char* av_b, struct blockchain *buffer)
{
    if (forget_global_block(av_b, buffer) == 1)
    {
        write(1, "This block doesn't exist.\n", my_strlen("This block doens't exist.\n"));
        return 1;
    }
    for (int i = 0; i < buffer->nodes.size; i++)
        forget_the_block_in_node(av_b, i, buffer);

    write(1, "Successfully removed block from all nodes.\n", my_strlen("Successfully removed block from all nodes.\n"));

    return 0;
}

int rm_case(char** av, int ac, int* i, struct blockchain* buffer)
{
    if (my_strcmp(av[*i], "node") == 0)
    {
        if (ac == 2)
        {
            write(1, "You should specify nid.\n", my_strlen("You should specify nid.\n"));
            return 1;
        }
        else if (rm_node(av[++(*i)], buffer) == 1) return 1;
    }
    else if (my_strcmp(av[*i], "block") == 0)
    {
        if (ac == 2)
        {
            write(1, "You should specify bid.\n", my_strlen("You should specify bid.\n"));
            return 1;
        }
        else if (rm_block(av[++(*i)], buffer) == 1) return 1;

        for (int i = 0; i < buffer->nodes.size; i++)
            for (int j = 0; j <  buffer->node_blocks[i].content_size; j++)
                write(1, buffer->node_blocks[i].content[j], my_strlen(buffer->node_blocks[i].content[j])); //REMOVE
    }
    else
    {
        write(1, "Command not found.\n", my_strlen("Command not found.\n"));
        return 1;
    }

    return 0;
}