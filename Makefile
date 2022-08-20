NAME = minishell
FLAGS = -Wall -Wextra -Werror -lreadline -L/Users/oel-berh/.brew/opt/readline/lib -I/Users/oel-berh/.brew/opt/readline/include

SRCS =	main.c \
		builtins/builtins.c \
		builtins/cd.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/exit.c \
		builtins/export_tools.c \
		builtins/export.c \
		builtins/more_tools.c \
		builtins/sort_exp.c \
		builtins/unset.c \
		execution/branch.c \
		execution/execute.c \
		execution/heredoc.c \
		parsing/constructor.c \
		parsing/correction.c \
		parsing/errors.c \
		parsing/expand_tools.c \
		parsing/ft_dsigne.c \
		parsing/parse.c \
		parsing/path.c \
		parsing/quotes.c \
		parsing/undo.c \
		tools/ft_atoi.c \
		tools/ft_itoa.c \
		tools/ft_split.c \
		tools/ft_splito.c \
		tools/ft_strjoin.c \
		tools/get_next_line.c \
		tools/sidekick.c \
		tools/special.c \
		tools/tools.c \

all : $(NAME)

$(NAME) : $(SRCS)
	@gcc $(FLAGS) $(SRCS) -o $(NAME) #-fsanitize=address

clean :
	@rm -rf $(NAME)
fclean :
	@rm -rf $(NAME)

re: fclean all