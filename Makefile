CC = cc
# valgrind --tool=helgrind ./philo 2 450 200 200
# -Wall -Wextra -Werror -fsanitize=thread
CFLAGS = -g -pthread -Wall -Wextra -Werror

SRC = init.c main.c utils.c

OBJ = $(SRC:.c=.o)

NAME = philo

ARG = 2 400 100 100

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
