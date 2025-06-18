CC = cc
# valgrind --tool=helgrind ./philo 2 450 200 200
# -Wall -Wextra -Werror -fsanitize=thread
# --read-var-info=yes : local variable, shows its name,
#  declaration point, and in which frame (of the first call stack) it lives
CFLAGS = -g -pthread -Wall -Wextra -Werror

SRC = init_bonus.c main_bonus.c utils_bonus.c generate_namesem.c \
		sad_life_routine_bonus.c ft_putendl_fd_bonus.c observer_bonus.c conditions_bonus.c

OBJ = $(SRC:.c=.o)

NAME = philo

ARG = 2 300 200 200

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

run : $(NAME)
	clear ; valgrind --tool=helgrind ./$(NAME) $(ARG)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re run
