CC = cc

CFLAGS = -g -pthread -Wall -Wextra -Werror

SRC = init_bonus.c main_bonus.c utils_bonus.c utils2_bonus.c utils3_bonus.c \
		sad_life_routine_bonus.c management_proc_bonus.c observer_bonus.c semaphore_bonus.c

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
