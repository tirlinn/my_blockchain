#include "my_blockchain.h"

int main()
{
    int file_fd;

    struct blockchain buffer;
    buffer.nodes.size = 0;
    buffer.nodes.values = malloc(sizeof(int) * 10);
    buffer.blocks.size = 0;
    buffer.blocks.list = malloc(sizeof(char*) * 10);
    buffer.node_blocks = malloc(sizeof(struct s_node_blocks) * 10);
    for (int i = 0; i < 10; i++)
    {
        buffer.node_blocks[i].content = malloc(sizeof(char*) * 10);
        buffer.node_blocks[i].content_size = 0;
    }

    if ((file_fd = open("blockchain", O_RDONLY)) > 2)
    {
        readbackup(file_fd, &buffer);
        close(file_fd);
    }

    prompt(&buffer);

    if ((file_fd = open("blockchain", O_CREAT | O_WRONLY | O_TRUNC)) > 2)
    {
        writebackup(file_fd, buffer);
        close(file_fd);
    }

    int troll = buffer.nodes.size + (10 - buffer.nodes.size % 10) * ((buffer.nodes.size % 10 + 9) / 10);
    for (int i = 0; i < troll; i++)
    {
        free(buffer.node_blocks[i].content);
    }
    free(buffer.node_blocks);
    free_arr(buffer.blocks.list, buffer.blocks.size);
    free(buffer.nodes.values);

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

char** sort_input(char* input, char separator, int* ac, char** av)
{
    *ac = 0;

    for (int i = 0; input[i]; i++)
    {
        if (input[i] == separator) continue;
        if (*ac % 10 == 0 && *ac != 0)
            av = my_realloc_arr(av, *ac, sizeof(char*) * (*ac + 10));
        av[*ac] = malloc(30);
        int j = 0;
        for (; input[i] != separator && input[i]; j++)
            av[*ac][j] = input[i++];
        av[*ac][j] = '\0';
        i--;
        (*ac)++;
    }

    return av;
}

int check_input(char* input, struct blockchain* buffer)
{
    char** av = malloc(sizeof(char*) * 10);
    int ac;
    int exit_status = 0;

    sort_input(input, ' ', &ac, av);

    for (int i = 0; i < ac && exit_status == 0; i++)
    {
        if (ac >= 2 && my_strcmp(av[i], "add") == 0)
        {
            i++;
            if (add_case(av, ac, &i, buffer) == 1)
                exit_status = 1;
        }
        else if (ac >= 2 && my_strcmp(av[i], "rm") == 0)
        {
            i++;
            if (rm_case(av, ac, &i, buffer) == 1)
                exit_status = 1;
        }
        else if (my_strcmp(av[i], "ls") == 0)
        {
            if (ac > 1)
                i++;
            if (ls_case(av[i], buffer) == 1)
                exit_status = 1;
        }
        else if (my_strcmp(av[i], "sync") == 0)
        {
            if (synchronise(buffer) == 1)
                exit_status = 1;
        }
        else if (my_strcmp(av[i], "quit") == 0)
            exit_status = -1;
        else
        {
            my_puts("Command not found.");
            exit_status = 1;
        }
    }

    free_arr(av, ac);

    return exit_status;
}

//void show_error(int exit_status)
//{
//    switch (exit_status)
//    {
//        case 1:
//            my_puts("E");
//        case 2:
//            my_puts("E");
//        case 3:
//            my_puts("E");
//        case 4:
//            my_puts("E");
//        case 5:
//            my_puts("E");
//        case 6:
//            my_puts("E");
//        case 7:
//            my_puts("E");
//        case 8:
//            my_puts("E");
//        case 9:
//            my_puts("E");
//        case 10:
//            my_puts("E");
//        case 11:
//            my_puts("E");
//        case 12:
//            my_puts("E");
//        case 13:
//            my_puts("E");
//        default:
//            my_puts("E");
//    }
//}

void prompt(struct blockchain* buffer)
{
    char* input;
    int exit_status;

    do
    {
        get_status(*buffer);
        input = my_readline(0);
        exit_status = check_input(input, buffer);
        //if (exit_status > 0)
        //    show_error(exit_status);
        free(input);
    } while (exit_status != -1);
}