NAME_BONUS = philo_bonus

CFLAGS = -Wall -Werror -Wextra -fsanitize=thread -g

SRCS_BONUS = philo_bonus.c \
	error_bonus.c \
	timer_bonus.c \
	outils_bonus.c \
	spxactivities.c

OBJS_BONUS = $(SRCS_BONUS:%.c=%.o)

all : $(NAME_BONUS)

$(NAME_BONUS) : $(OBJS_BONUS)
	$(CC) $(OBJS_BONUS) -o $(NAME_BONUS) $(CFLAGS)

clean :
	rm $(OBJS_BONUS)

fclean : clean
	rm $(NAME_BONUS)

re : fclean all