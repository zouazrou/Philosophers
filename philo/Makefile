CC = cc

CFLAGS = -g -pthread -Wall -Wextra -Werror

SRC = init.c main.c utils.c utils2.c observer.c get_value.c sad_life_routine.c ft_putendl_fd.c

OBJ = $(SRC:.c=.o)

NAME = philo

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
