CC = gcc
CFLAGS = -g3 -fsanitize=address -Wall -Werror -Wextra
INCLUDES = -I./
SRCS = my_blockchain.c my_add_case.c my_func.c
OBJS = $(SRCS:.c=.o)
MAIN = my_blockchain

.PHONY: depend clean

all:    $(MAIN) clean_o
	@echo  Simple compiler named $(MAIN) has been compiled.

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) #$(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean_o:
	$(RM) *.o

clean:
	$(RM) *.o $(MAIN)
