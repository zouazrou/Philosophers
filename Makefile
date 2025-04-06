CC = cc
# valgrind --tool=helgrind ./philo 2 450 200 200
# -Wall -Wextra -Werror -fsanitize=thread
CFLAGS = -g -pthread -Wall -Wextra -Werror

SRC = init_handling_errs.c main.c ft_atoi.c

OBJ = $(SRC:.c=.o)

NAME = philo

ARG = 2467 7000 500 10999

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

run : $(NAME)
	clear ; ./$(NAME) $(ARG)
clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re run
