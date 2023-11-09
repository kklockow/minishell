CC = cc
NAME = minishell
CFLAGS = -Wall -Werror -Wextra

SOURCE =	src/main.c

OBJECTS = $(SOURCE:.c=.o)

$(NAME) : $(OBJECTS)
	@$(CC) $(OBJECTS) -o $(NAME) -lreadline

all : $(NAME)

clean:
	@rm -f $(OBJECTS)

fclean:
	@rm -f  $(OBJECTS) $(NAME)

re: fclean all

.PHONY : clean fclean all re