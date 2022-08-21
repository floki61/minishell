/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:57 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/21 20:02:21 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <limits.h>

# define BLUE    "\e[0;34m"
# define RED     "\e[0;31m"
# define GREEN   "\e[0;32m"
# define YELLOW  "\e[1;33m"
# define RESET   "\e[0m"

int	g_exit_status;

enum e_define
{
	EXEC,
	PIPE,
	REDIR,
} ;

typedef struct t_list
{
	char			*name;
	char			*value;
	char			*sep;
	struct t_list	*next;
}	t_list;

typedef struct t_cmd
{
	int	type;
}	t_cmd;

typedef struct t_tool
{
	char	*limiter;
	char	*path;
	char	**envp;
	int		in;
	int		out;
	int		free;
	int		stdin_copy;
	int		stdout_copy;
	int		fd;
}	t_tool;

typedef struct t_pipe
{
	int				type;
	struct t_cmd	*left;
	struct t_cmd	*right;
}	t_pipe;

typedef struct t_exec
{
	int		type;
	char	**args;
}	t_exec;

typedef struct t_redir
{
	int				type;
	struct t_cmd	*exe;
	char			*file;
	int				mode;
	int				fd;
	int				token;
}	t_redir;

typedef struct t_quote
{
	int	*quote;
	int	x;
	int	start;
}	t_quote;

int		ft_strlen(char *str);
char	*clean(char *str);
int		ft_limites(char *str);
t_cmd	*end_it(t_cmd *cmd);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c, int access);
char	**ft_advanced(char const *s, char *buf);
char	*get_path(t_exec *exe, t_list **data);
int		lets_check(char *str);
char	*ft_path(char *line);
int		followed(char *s, int *i);
t_cmd	*piping(t_cmd *left, t_cmd *right);
t_cmd	*redirect(t_cmd	*exe, char *file, int mode, int fd);
t_cmd	*exelior(char *s);
void	free_tab(char **path, int i);
int		ft_strchr(char s, char *scan);
int		ft_skip(char *s, char *skip);
int		exist(char **ps, char *token);
int		get_token(char **ps, char **q);
t_cmd	*parsecmd(char *str, t_list **env);
t_cmd	*parsepipe(char	*ps, t_list **env, t_quote quote);
t_cmd	*parsered(t_cmd	*cmd, char **ps, t_list **env, t_quote *quote);
void	run_cmd(t_cmd *cmd, t_tool *tools, t_list **data);
int		ft_strncmp(const char *first, const char *second, size_t length);
int		if_builtins(char **inpt, t_list **data);
void	ft_skip_spaces(char *inpt, int *i);
char	*if_dsigne(char *inpt, t_list **env, t_quote *quote);
char	*quotes(char *str, t_quote *quote);
void	handle_c(int sig);
void	handle_s(int sig);
char	*get_next_line(int fd);
char	**if_echo(char *str);
int		wd_count(const char *str, char c, int access);
int		tokenizer(char *str, int *x);
char	*no_space(char *str);
int		ft_echo(char **cmd);
char	**ft_splito(char const *s, char c);
int		spaces_still(char *str);
int		ft_strcmp(char *s1, char *s2);
int		num_quotes(char *str, char c);
void	accountant(char **str, int i, int *dollar);
char	**cashier(char *str);
char	*after_world(char *str);
char	*exdsigne(char *op, char **env);
char	**forenv(char **env);
int		exec_args(t_exec **exec, int i, char **ps);
char	*corrected(char *line, char *str);
void	type_pipe(t_cmd *cmd, t_tool *tools, t_list **data);
void	type_exec(t_cmd *cmd, t_tool *tools, t_list **data);
void	type_redir(t_cmd *cmd, t_tool *tools, t_list **data);
void	heredoc(t_redir *red, t_tool *tools);
void	exe_doc(char *buf, t_exec *exe, t_tool *tools, t_list **data);
void	ft_putstr_fd(char *s, int fd);
int		is_alnum(int c);
int		ifenv(t_cmd *cmd, t_list **data);
int		ifexit(t_cmd *cmd);
int		ft_cd(char **inpt, t_list **env);
void	ft_envp(char **envp, t_list **data);
int		printenvp(char **inpt, t_list **data);
t_list	*ft_lstnew(void *name, void *value, void *sep);
void	ft_lstadd_back(t_list **alst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_export(char **cmd, t_list **data);
int		ft_unset(char **cmd, t_list **data);
int		bult_2(char	**inpt, t_list **data);
char	*ft_itoa(int n);
char	*undo(char *str, int c);
char	*sq_undo(char *var);
char	**dq_undo(char *var);
char	*assigning(char *more, char *end, t_list **env, int *thief);
void	free_struct(t_cmd *cmd);
int		v_position(char *str, char c);
char	*skip_c(char *str, char c);
int		withvalue(char *cmd, t_list **data);
int		existkey(char *cmd, char **op, t_list **data, char c);
int		check_exp(char *str);
void	print_exp(t_list *data);
int		should_open(t_redir *red);
void	inside_quotes(char *str, int *i);
void	if_quote(const char *str, int *i);
int		no_quote(const char *str, int i, char c);
int		error_scanner(char *str);
int		inside_string(char *s, int i);
void	next_quote(char *str, int *i, int *x, int tmp);
int		ft_atoi(char *str);
void	fperror(char *arg, char *error);
char	*ft_itoa(int n);
char	*findkey(char *key, t_list **env);
int		ft_pwd(char **inpt);
char	*ft_strdup(const char *src);
t_cmd	*which_redir(t_cmd *cmd, char *clear, int token);
t_cmd	*parser(char **ps, t_list **env, t_quote *quote, int *i);

#endif