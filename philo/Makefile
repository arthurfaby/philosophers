# Makefile generate by afaby

# Name of the executable
NAME	=	philo

# Path of your headers
INC_DIR	=	.
INC		=	-I $(INC_DIR)

# Compiler to use
CC		=	gcc

# Flags to use
CFLAGS	=	-Wall -Wextra -Werror -pthread -g

# All the sources
SRCS	=	philosophers.c \
			message.c

OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INC)

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: re fclean clean all
