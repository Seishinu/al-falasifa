NAME = philo

CFLAGS = -Wall -Werror -Wextra

SRCS = philo.c \
	timer.c \
	routini_lyawmi.c \
	error_checking.c \

OBJS = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm $(NAME)

re : fclean all