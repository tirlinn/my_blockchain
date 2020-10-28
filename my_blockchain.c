#include "my_blockchain.h"

//
// values = {1, 2};
// size = 4;
// list = {10, 20, 30, 40};
// node_blocks_number = {4, 4};
// node_block = { {"10", "20", "30", "40"} , {"10", "20", "30", "40"} };

int main()
{
    int file_fd = open("blockchain", O_CREAT || O_RDWR);

    struct blockchain *buffer = malloc(sizeof(struct blockchain));
    buffer->nodes.size = 0;
    buffer->nodes.values = malloc(sizeof(int) * 10);
    buffer->blocks.size = 0;
    buffer->blocks.list = malloc(sizeof(char*) * 10);
    for (int i = 0; i < 10; i++)
        buffer->node_blocks = malloc(sizeof(struct s_node_blocks) * 10);
    for (int i = 0; i < 10; i++)
        buffer->node_blocks[i].content = malloc(sizeof(char*) * 10);

    // buffer = READBACKUP ????;

    buffer = prompt(buffer);

    // WRITEBACKUP ???;

    close(file_fd);

    return 0;
}

char* is_sync(struct blockchain buffer)
{
    for (int i = 0; i < buffer.nodes.size; i++)
        if (buffer.blocks.size != buffer.node_blocks[i].content_size)
            return "-";
    return "s";
}

void get_status(struct blockchain buffer)
{
    char output[18];
    char tmp[16];
    my_strcpy(output, "[");
    my_strcat(output, is_sync(buffer));
    my_itoa(tmp, buffer.nodes.size);
    my_strcat(output, tmp);
    my_strcat(output, "]> ");
    write(1, output, my_strlen(output));
}

char** sort_input (char* input, int* ac, char** av)
{
    av = malloc(sizeof(char*)*10);
    *ac = 0;

    for (int i = 0; input[i]; i++)
    {
        if (input[i] == ' ') continue;
        av[*ac] = malloc(30);
        int j = 0;
        for (; input[i] != ' ' && input[i]; j++)
            av[*ac][j] = input[i++];
        av[*ac][j] = '\0';
        i--;
        (*ac)++;
    }

    return av;
}

// void ls_case(char* av_i, struct blockchain* buffer)
// {
//     switch (0)
//     {
//         case my_strcmp(av_i, "-l"):
//             list_blocks();//INCOMPLETE
//             break;
//
//         default:
//             list_nodes();//INCOMPLETE
//             break;
//     }
// }

int check_input(char* input, struct blockchain* buffer)
{
    int ac;

    char** av = sort_input(input, &ac, av);

    for (int i = 0; i < ac; i++)
    {
        if (my_strcmp(av[i], "add") == 0)
        {
            i++;
            if ( add_case(av, &i, buffer) == 1 ) return 1;
        }
        // else if (my_strcmp(av[i], "rm") == 0)
        // {
        //     i++;
        //     if ( rm_case(av, &i) == 1) return 1;
        // }
        // else if (my_strcmp(av[i], "ls") == 0)
        // {
        //     i++;
        //     ls_case(av[i]);                     //INCOMPLETE
        // }
        // else if (my_strcmp(av[i], "sync") == 0)
        // {
        //     synchronise();                      //INCOMPLETE
        // }
        else if (my_strcmp(av[i], "quit") == 0)
        {
            return -1;
        }
        else
        {
            printf("Command not found.");
            return 1;
        }
    }

    return 0;
}

// void (exit_status)
// {
//     if (1)
//         printf(dsafdsaf)
//     if (2)
//         printf(asdfasdf)
// }

char* my_readline()
{
    char *buffer = malloc(1);
    int read_size = 1;
    int buf_size = 0;

    while( read_size )
    {
        buffer = my_realloc_str(buffer, buf_size, (buf_size + 100 + 1) );
        read_size = read(0, &buffer[buf_size], 100);
    }

    return buffer;
}

struct blockchain *prompt(struct blockchain *buffer)
{
    char *input;
    int exit_status;

    do
    {
        get_status(*buffer);
        input = my_readline();
        exit_status = check_input(input, buffer);
        // if (exit_status > 0)
        //     error show;
        free(input);
    }
    while ( exit_status != -1 );

    return buffer;
}
