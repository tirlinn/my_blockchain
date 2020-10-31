#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

struct s_nodes
{
    int size;
    int* values;
};

struct s_blocks
{
    int size;
    char** list;
};

struct s_node_blocks
{
    int content_size;
    char** content;
};

struct blockchain
{
    struct s_nodes nodes;
    struct s_blocks blocks;
    struct s_node_blocks* node_blocks;
};

//my_func.c
int my_strcmp(const char* s1, const char* s2);
int my_strlen(char* param_1);
void my_strcpy(char* str1, char* str2);
void my_strcat(char* str1, char* str2);
int* my_realloc_int(int* array, int size, int new_size);
char* my_realloc_str(char* string, int old_size, int size);
char** my_realloc_arr(char** arr, int old_size, int size);
struct s_node_blocks* my_realloc_struct(struct s_node_blocks* structure, int old_size, int new_size);
int my_atoi(const char* input);
void my_itoa(char* p1, int p2);
//my_add_case.c
void remember_node(int input, int tmp, struct blockchain* buffer);
int add_node(char* av_i, struct blockchain* buffer);
void remember_global_block(char* av_b, struct blockchain* buffer);
void remember_node_block(char* av_b, int n_pos, int b_pos, struct blockchain* buffer);
bool find_node_block_pos(char* av_b, int n_pos, int* b_pos, struct blockchain* buffer);
int add_block(char* av_b, char* av_i, struct blockchain* buffer);
int add_case(char** av, int ac, int* i, struct blockchain* buffer);
//my_blockchain.c
char* is_sync(struct blockchain buffer);
void sort_input(char* input, int* ac, char** av);
int check_input(char* input, struct blockchain* buffer);
void prompt(struct blockchain* buffer);
char* my_readline();
//my_remove_case.c
bool find_node_pos(int* pos, int input, struct blockchain* buffer);
bool block_unique(int pos, char* str, struct blockchain* buffer);
void forget_the_node_blocks(int pos, struct blockchain* buffer);
void forget_the_node(int pos, struct blockchain* buffer);
int rm_node(char* av_i, struct blockchain* buffer);
bool find_global_block(char* av_b, int* pos, struct blockchain* buffer);
int forget_global_block(char* av_b, struct blockchain* buffer);
void forget_the_block_in_node(char* av_b, int n_pos, struct blockchain* buffer);
int rm_block(char* av_b, struct blockchain* buffer);
int rm_case(char** av, int ac, int* i, struct blockchain* buffer);