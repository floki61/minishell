NAME = minishell
FLAGS = -Wall -Wextra -Werror -lreadline -L/Users/oel-berh/.brew/opt/readline/lib -I/Users/oel-berh/.brew/opt/readline/include

SRCS =	main.c \
		echo.c \
		ft_split.c \
		ft_strjoin.c \
		ft_atoi.c 		\
		path.c \
		constructor.c \
		tools.c \
		execute.c \
		parse.c \
		builtins.c \
		ft_dsigne.c \
		advanced.c \
		get_next_line.c \
		ft_splito.c \
		expand_tools.c \
		correction.c \
		quotes.c \
		sidekick.c  \
		branch.c \
		env.c \
		export.c \
		ft_itoa.c \
		more_tools.c \
		unset.c \

all : $(NAME)

$(NAME) : $(SRCS)
	@gcc $(FLAGS) $(SRCS) -o $(NAME)

clean :
	@rm -rf $(NAME)
fclean :
	@rm -rf $(NAME)

re: fclean all
