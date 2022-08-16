NAME = minishell
FLAGS = -Wall -Wextra -Werror -lreadline -L/Users/oel-berh/.brew/opt/readline/lib -I/Users/oel-berh/.brew/opt/readline/include

SRCS =	main.c \
		path.c \
		constructor.c \
		tools.c \
		execute.c \
		parse.c \
		ft_dsigne.c \
		advanced.c \
		expand_tools.c \
		correction.c \
		quotes.c \
		sidekick.c  \
		branch.c \
		tools/ft_split.c 		\
		tools/ft_strjoin.c 		\
		tools/ft_atoi.c 		\
		tools/get_next_line.c 	\
		tools/ft_splito.c 		\
		tools/ft_itoa.c 		\
		builtins/builtins.c 	\
		builtins/cd.c 			\
		builtins/echo.c 		\
		builtins/env.c 			\
		builtins/exit.c 		\
		builtins/export.c		\
		builtins/export_tools.c \
		builtins/more_tools.c 	\
		builtins/sort_exp.c 	\
		builtins/unset.c 		\

all : $(NAME)

$(NAME) : $(SRCS)
	@gcc $(FLAGS) $(SRCS) -o $(NAME)

clean :
	@rm -rf $(NAME)
fclean :
	@rm -rf $(NAME)

re: fclean all
