#include "my_blockchain.h"

int add_node(char* av_i, struct blockchain *buffer)
{
    int tmp;
    int input;
    if ( (input = my_atoi(av_i)) < 0)
    {
        printf("Error.");
        return 1;
    }

    for (int i = 0; i < buffer->nodes.size; i++)
        if (input == buffer->nodes.values[i])
        {
            printf("This node already exists.\n");
            return 1;
        }

    buffer->nodes.size++;
    tmp = buffer->nodes.size;
    if (tmp % 10 == 0)
    {
        buffer->nodes.values = my_realloc_int(buffer->nodes.values, tmp-1, sizeof(int)*(tmp + 10));
        buffer->node_blocks = my_realloc_struct(buffer->node_blocks, sizeof(struct node_blocks)*tmp, sizeof(struct node_blocks) *(tmp + 10));
        for (int i = tmp; i < tmp + 10; i++)
            buffer->node_blocks[tmp].content = malloc(sizeof(char*) * 10);
    }
    buffer->nodes.values[tmp] = input;
    buffer->node_blocks[tmp].content_size = 0;

    return 0;
}

void remember_block(char* av_b, struct blockchain *buffer)
{
    int i;

    for(i = 0; i < buffer->blocks.size; i++)
        if (my_strcmp(av_b, buffer->blocks.list[i]) == 0) break;

    if (i == buffer->blocks.size)
    {
        buffer->blocks.size++;
        int tmp = buffer->blocks.size;
        if(tmp%10 == 0)
            buffer->blocks.list = my_realloc_str(buffer->blocks.list, tmp - 1, sizeof(char*) * (tmp + 10));
        buffer->blocks.list[tmp] = malloc(sizeof(char) * (my_strlen(av_b) + 1));
        my_strcpy(buffer->blocks.list[tmp], av_b);
    }
}

void add_block(char* av_b, char* av_i, struct blockchain *buffer)
{
    int pos;
    // add new block to struct blocks if it doesn't exis
    remember_block(av_b, buffer);
    //find position of the node in struct nodes.
    for (pos = 0; pos < buffer->nodes.size; pos++)
        if (my_strcmp(av_i, buffer->nodes.values[pos]) == 0) break;
    // check if the node already exists
    if (pos == buffer->nodes.size)
    {
        printf("Node doesn't exist.");
        return 1;
    }
    //check if the block already exists
    for (int j = 0; j < buffer->node_blocks->content_size; j++)
        if (my_strcmp(av_b, buffer->node_blocks->content[j]) == 0)
        {
            printf("This block already exists.\n");
            return 1;
        }
    //add block to the node
    buffer->node_blocks[pos].content_size++;
    tmp = buffer->node_blocks[pos].content_size;
    if(tmp%10 == 0)
        buffer->node_blocks[pos].content = my_realloc_int(buffer->node_blocks.values, tmp - 1, sizeof(char*) * (tmp + 10);
    buffer->node_blocks[pos].content[tmp] = malloc(sizeof(char)*(my_strlen(av_b) + 1));
    my_strcpy(buffer->node_blocks[pos].content[tmp], av_b);

    return 0;
}

int add_case (char** av, int *i, struct blockchain* buffer)
{
    switch (0)
    {
        case my_strcmp(av[*i], "node"):
            if (!av[++(*i)])
            {
                printf("You should specify nid.");
                return 1;
            }
            if (add_node(av[*i], buffer) == 1) return 1;
            break;

        case my_strcmp(av[*i], "block"):
            if (!av[++(*i)])
            {
                printf("You should specify bid.");
                return 1;
            }
            if (!av[(*i) + 1])
            {
                printf("You should specify nid.");
                return 1;
            }
            while(av[++(*i)])
                add_block(av[2], av[*i], buffer);
            break;

        default:
            printf("Command not found.");
            return 1;
    }

    return 0;
}
