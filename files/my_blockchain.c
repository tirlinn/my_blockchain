#include "my_blockchain.h"

int main()
{
    int file_fd;

    struct blockchain buffer;
    buffer.nodes.size = 0;
    buffer.nodes.values = malloc(sizeof(int) * 10);
    buffer.blocks.size = 0;
    buffer.blocks.list = malloc(sizeof(char*) * 10);
    for (int i = 0; i < 10; i++)
        buffer.node_blocks = malloc(sizeof(struct s_node_blocks) * 10);
    for (int i = 0; i < 10; i++)
    {
        buffer.node_blocks[i].content = malloc(sizeof(char*) * 10);
        buffer.node_blocks[i].content_size = 0;
    }

    if ((file_fd = open("blockchain", O_RDONLY)) > 2)
    {
        // READBACKUP ????;
        close(file_fd);
    }

    prompt(&buffer);

    if ((file_fd = open("blockchain", O_CREAT | O_WRONLY | O_TRUNC)) > 2)
    {
        writebackup(file_fd, buffer);
        close(file_fd);
    }

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

void sort_input(char* input, int* ac, char** av)
{
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
}

int check_input(char* input, struct blockchain* buffer)
{
    char** av = malloc(sizeof(char*) * 10);
    int ac;

    sort_input(input, &ac, av);

    for (int i = 0; i < ac; i++)
    {
        if (ac >= 2 && my_strcmp(av[i], "add") == 0)
        {
            i++;
            if (add_case(av, ac, &i, buffer) == 1) return 1;
        }
        else if (ac >= 2 && my_strcmp(av[i], "rm") == 0)
        {
            i++;
            if (rm_case(av, ac, &i, buffer) == 1) return 1;
        }
        else if (my_strcmp(av[i], "ls") == 0)
        {
            if (ac > 1)
                i++;
            if (ls_case(av[i], buffer) == 1) return 1;
        }
        else if (my_strcmp(av[i], "sync") == 0)
        {
            if (synchronise(buffer) == 1) return 1;
        }
        else if (my_strcmp(av[i], "quit") == 0)
        {
            return -1;
        }
        else
        {
            write(1, "Command not found.\n", 19);
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
    char* input = malloc(1);
    int read_size = 1;
    int buf_size = 0;
    int i = 0;

    while (read_size)
    {
        input = my_realloc_str(input, buf_size, (buf_size + 101));
        read_size = read(0, &input[buf_size], 100);
        buf_size = buf_size + 100;

        for (; i < buf_size; i++)
            if (input[i] == '\n')
            {
                input[i] = '\0';
                read_size = 0;
                break;
            }
    }
    return input;
}

void prompt(struct blockchain* buffer)
{
    char* input;
    int exit_status;

    do
    {
        get_status(*buffer);
        input = my_readline();
        exit_status = check_input(input, buffer);
        // if (exit_status > 0)
        //     error show;
        free(input);
    } while (exit_status != -1);
}