NAME	=	philo
SRCS	=	main.c \
			ft_atoi.c \
			ft_itoa.c \
			error.c\
			routine.c \
			eat.c \
			monitor.c \
			utils.c \
			initialize.c
OBJS	= $(SRCS:.c=.o)
CC		= gcc
FLAGS	= -Wall -Wextra -Werror -fsanitize=address -g
HEADER_FILE = /rewrite/philo.h

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADER_FILE)
	$(CC) -c $(FLAGS) -o $@ $<

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
