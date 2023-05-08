NAME = server client
SERVER = server
CLIENT = client	
CC = gcc
NORM = norminette
CFLAGS = -Wall -Wextra -Werror -g -O0
RM = rm -rf

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all : $(SERVER) $(CLIENT)

bonus : all

$(CLIENT) : client.o utils.o
	$(CC) $(CFLAGS) $^ -o $@

$(SERVER) : server.o utils.o
	 $(CC) $(CFLAGS) $^ -o $@

clean : 
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

norm : 
	$(NORM) $(SRCS)

re : fclean all

.PHONY : clean fclean re all bonus
