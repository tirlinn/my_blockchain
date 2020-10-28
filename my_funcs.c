#include "my_blockchain.h"

int my_strcmp(const char* s1, const char* s2)
{
    for (int i = 0; s1[i] || s2[i]; i++)
        if (s1[i] != s2[i]) return s1[i] - s2[i];
    return 0;
}

int my_strlen(char* param_1)
{
    for (int i = 0;; i++)
        if (!param_1[i]) return i;
}

void my_strcpy (char* str1, char* str2)
{
    for (int i = 0; (str1[i] = str2[i]); i++);
}

void my_strcat (char* str1, char* str2)
{
    for (int i = my_strlen(str1); (str1[i] = str2[i]); i++);
}

int* my_realloc_int(int* array, int size, int new_size)
{
    int* out = malloc(sizeof(int) * new_size);
    for(int i = 0; i < size; i++)
        out[i] = array[i];
    free(array);
    return out;
}

char* my_realloc_str(char* string, int old_size, int size)
{
    char* out = malloc(size);
    for (int i = 0; i < old_size ; i++)
        out[i] = string[i];
    free(string);
    return out;
}

struct s_node_blocks *my_realloc_struct(struct s_node_blocks *structure, int old_size, int new_size)
{
    struct s_node_blocks *output = malloc(sizeof(struct s_node_blocks)*new_size);
    for (int i = 0; i < old_size; i++)
    {
        output[i].content = structure[i].content;
    }
    output->content_size = structure->content_size;
    for (int i = old_size; i < new_size; i++)
    {
        output[i].content = malloc(sizeof(char*) * 10);
    }
    free(structure);
    return output;
}

int my_atoi(const char* input)
{
    int buffer = 0, cur_val = 0, sign = 1;
    int i = 0;

    if (input[0] == '-')
    {
        printf("Node cannot be a negative value.\n");
        return -1;
    }
    if (input[0] == '+') i++;

    while (input[i])
    {
        if (input[i] < '0' || input[i] > '9')
        {
            printf("Node should be a digit.\n");
            return -1;
        }
        cur_val = (input[i] - '0');
        buffer = buffer * 10 + cur_val;
        i++;
    }

    return sign * buffer;
}

void my_itoa(char* p1, int p2)
{
    char out_0[16];
    char* out = &out_0[15];
    *out = '\0';

    do
    {
        *--out = '0' + p3 % 10;
        p3 /= 10;
    }
    while ( p3 );

    my_strcpy(p1 , out);
}

my_itoa
my_atoi

my_realloc_int
my_realloc_str
my_realloc_struct
