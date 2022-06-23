NAME = minishell
FLAGS = -Wall -Wextra -Werror -lreadline

SRCS =	main.c \
		ft_split.c \
		ft_strjoin.c \
		path.c \

all : $(NAME)

$(NAME) : $(SRCS)
	@gcc $(FLAGS) $(SRCS) -o $(NAME)

clean :
	@rm -rf $(NAME)
fclean :
	@rm -rf $(NAME)

re: fclean all