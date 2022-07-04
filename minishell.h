/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:57 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/04 01:28:29 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

// #define	EXEC 1
// #define	PIPE 2
// #define	REDIR 3

enum e_define
{
	EXEC,
	PIPE,
	REDIR,
} ;

typedef struct t_cmd
{
	int	type;
}	t_cmd;

typedef struct t_pipe
{
	int				type;
	struct t_cmd	*left;
	struct t_cmd	*right;
}	t_pipe;


//exec in case running a program
//args for filename
//and eargs for argv
typedef struct t_exec
{
	int		type;
	char	*args[10];
	char	*erags[10];
}	t_exec;

//fd is gonna be either 0 or 1
typedef struct t_redir
{
	int				type;
	struct t_cmd	*exe;
	char			*file;
	char			*efile;
	int				mode;
	int				fd;
}	t_redir;


int	    ft_strlen(char *str);
t_cmd	*end_it(t_cmd *cmd);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*get_path(t_exec *exe, char **envp);
int		lets_check(char *str);
int		followed(char **s);
t_cmd	*piping(t_cmd *left, t_cmd *right);
t_cmd	*redirect(t_cmd	*exe, char *file, char *efile, int mode, int fd);
t_cmd	*exelior();
int		ft_strchr(char s, char *scan);
int		ft_skip(char *s, char *skip);
int		exist(char **str, char *token);
int		get_token(char **str, char **q, char **eq);
t_cmd	*parsecmd(char *str);
t_cmd	*parsepipe(char	**str);
t_cmd	*parsered(t_cmd	*cmd, char **str);
void	run_cmd(t_cmd *cmd, char **envp, int *c);
int		ft_strncmp(const char *first, const char *second, size_t length);
int if_builtins(char *buf);
#endif