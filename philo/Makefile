NAME = philo

CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread

SRCS = philo.c \
	outils.c \
	timer.c \
	philo_routine.c \
	error_checking.c \

OBJS = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all