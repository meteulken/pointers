NAME = minishell

SRC = minishell.c utils.c builtins.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ) -lreadline

fclean: clean
	@rm -f $(NAME)

clean:
	@rm -f $(OBJ)

re: fclean all
