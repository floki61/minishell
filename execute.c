/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:54:07 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/11 05:14:58 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	followed(char **s)
{
	int		token;
	char	*p;

	p = *s;
	if (*p == '<')
	{
		token = '<';
		p++;
		if (*p == '<')
		{
			p++;
			token = '-';
			*s = p;
			return (token);
		}
		*s = p;
		return (token);
	}
	else if (*p == '>')
	{
		token = '>';
		p++;
		if (*p == '>')
		{
			p++;
			token = '+';
			*s = p;
			return (token);
		}
		*s = p;
		return (token);
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write (fd, &s[i], 1);
			i++;
		}
	}
}

char	*clean(char *str)
{
	int		i;
	char	*clean;

	i = 0;
	while (str[i] != '\0' && !ft_strchr(str[i], " \t\n\f\v\r"))
		i++;
	clean = malloc (sizeof(char) * i);
	i = 0;
	while (str[i] != '\0' && !ft_strchr(str[i], " \t\n\f\v\r"))
	{
		clean[i] = str[i];
		i++;
	}
	clean[i] = '\0';
	return (clean);
}

char	*quotes(char *str, t_quote *quote)
{
	int		i;
	int		j;
	int		x;
	int		sign;
	char	*buf;

	i = 0;
	j = 0;
	x = 0;
	sign = 0;
	while (str[i])
	{
		//str[i] == 1 && str[i + 1] == 1
		//print until u find the same quote and so on
		//1 means double quote and 2 means single quote
		if (str[i] == 34)
		{
			//printf ("double quote %d %d\n", i, sign);
			if (i + 1 <= sign)
				(quote->quote[x]) = 1;
			str[i] = 1;
			//if len == 0 check segv "" | ''
			while (str[i] && str[i] != 34)
				i++;
			if (str[i] == '\0')
			{
				printf ("minishell: quotation error\n");
				exit (1);
			}
			str[i] = 1;
		}
		else if (str[i] == 39)
		{
			//printf ("single quote %d %d\n", i, sign);
			if (i + 1 <= sign)
				(quote->quote[x]) = 2;
			str[i] = 1;
			while (str[i] && str[i] != 39)
				i++;
			if (str[i] == '\0')
			{
				printf ("minishell: quotation error\n");
				exit (1);
			}
			if (i + 1 == sign)
				(quote->quote[x]) = 1;
			str[i] = 1;
		}
		i++;
		if (str[i] == ' ' || str[i] == 34 || str[i] == 39)
		{
			//printf ("quote %d = %d\n", x, quote->quote[x]);
			x++;
			while (str[j])
			{
				if (str[j] == 34)
				{
					j++;
					while (str[j] && str[j] != 34)
					{
						if (str[j] == '$')
							sign = j;
						j++;
					}
					if (str[j])
						j++;
					break ;
				}
				else if (str[j] == 39)
				{
					j++;
					while (str[j] && str[j] != 39)
					{
						if (str[j] == '$')
							sign = j;
						j++;
					}
					if (str[j])
						j++;
					break ;
				}
				else
				{
					if (str[j] == '$')
					{
						sign = j;
						break ;
					}					
				}
				j++;
			}
			if (str[i] == ' ')
				i++;
		}
	}
	buf = malloc (sizeof(char) * ft_strlen(str) + 1);
	x = 0;
	j = 0;
	while (str[j])
	{
		buf[x] = str[j];
		x++;
		j++;
	}
	buf[x] = '\0';
	//return char allocated with the right size and quote by reference
	//printf ("quote : %s\n", buf);
	return (buf);
}

static char	*get_cmd(t_exec *exe, char **envp, int i)
{
	int		j;
	char	*path;
	char	**cmd;

	j = -1;
	path = envp[i];
	cmd = ft_split(&path[5], ':', 0);
	if (access(exe->args[0], F_OK | X_OK) != -1)
		return (exe->args[0]);
	while (cmd[++j])
	{
		cmd[j] = ft_strjoin(cmd[j], "/");
		cmd[j] = ft_strjoin(cmd[j], exe->args[0]);
		if (access(cmd[j], F_OK) != -1)
			return (cmd[j]);
	}
	printf ("minishell: %s: command not found\n", exe->args[0]);
	exit (127);
}

char	*get_path(t_exec *exe, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (envp[i][0] == 'P')
		{
			if (ft_strncmp(envp[i], "PATH=", 5) == 0)
				return (get_cmd(exe, envp, i));
		}
	}
	return (0);
}

void	run_cmd(t_cmd *cmd, char **envp, t_tool *tools, t_list **data, char **path)
{
	int		i;
	int		p[2];
	int 	bult;
	char	*buf;
	char	**end;
	char	*ar;
	t_exec	*exe;
	t_pipe	*pip;
	t_redir	*red;
	t_redir	*red2;

	i = 0;
	ar = NULL;
	if (cmd == 0)
		exit (1);
	if (cmd->type == EXEC)
	{
		exe = (t_exec *)cmd;
		if (exe->args[0] == 0)
			exit (1);
		bult = if_builtins(exe->args, data, path);
		if (bult)
		{
			if(bult == 2)
				exit(0);
			exit(bult);
		}
		buf = get_path(exe, envp);
		if (tools->limiter != NULL)
		{
			end = ft_splito(tools->limiter, ' ');
			while ((ar = get_next_line(0)))
			{
				if (ft_strcmp(end[i], ar) == 0)
				{
					i++;
					if (end[i] == 0)
					{
						close(tools->fd);
						tools->fd = open("/tmp/ ", O_RDONLY, 0644);
						dup2(tools->fd, STDIN_FILENO);
						execve(buf, exe->args, envp);
					}
				}
				else
					ft_putstr_fd(ar, tools->fd);
			}
		}
		execve(buf, exe->args, envp);
	}
	else if (cmd->type == PIPE)
	{
		pip = (t_pipe *)cmd;
		if (pipe(p) == -1)
		{
			printf ("An error occured in the pipe function\n");
			exit (1);
		}
		if (fork() == 0)
		{
			dup2(p[1], STDOUT_FILENO);
			close(p[0]);
			close(p[1]);
			run_cmd(pip->left, envp, tools, data, path);
			if (pip->left->type == EXEC)
				exit (1);
		}
		else
		{
			if (pip->left->type == REDIR)
				wait(0);
			dup2(p[0], STDIN_FILENO);
			close(p[0]);
			close(p[1]);
			run_cmd(pip->right, envp, tools, data, path);
			if (pip->right->type == EXEC)
				exit (1);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
	}
	else if (cmd->type == REDIR)
	{
		red = (t_redir *)cmd;
		red2 = (t_redir *)red->exe;
		if (red->token == 4)
		{
			red->file = ft_strjoin(red->file, " ");
			tools->c = 1;
			tools->fd = open("/tmp/ ", O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (tools->fd < 0)
			{
				printf ("Error\n");
				exit(1);
			}
			dup2(tools->stdin_copy, 0);
			tools->limiter = ft_strjoin(red->file, tools->limiter);
			if (red->exe->type == EXEC)
			{
				exe = (t_exec *)red->exe;
				if (exe->args[0] == 0)
				{
					end = ft_splito(tools->limiter, ' ');
					i = 0;
					while ((ar = get_next_line(0)))
					{
						if (ft_strcmp(end[i], ar) == 0)
						{
							i++;
							if (end[i] == 0)
							{
								close(0);
								exit(1) ;
							}
						}
						else
							ft_putstr_fd(ar, tools->fd);
					}
				}
			}
		}
		else
		{
			tools->fd = open(red->file, red->mode, 0644);
			if (tools->fd < 0)
			{
				printf ("Errooor\n");
				exit (1);
			}
		}
		if (tools->c != 1)
		{
			dup2(tools->fd, red->fd);
			if (red->exe->type == REDIR)
			{
				if (red->fd == red2->fd)
					(tools->c) = 1;
			}
		}
		if (red->exe->type == REDIR)
			{
				if (red->fd != red2->fd)
					(tools->c) = 0;
			}
		run_cmd(red->exe, envp, tools, data, path);
	}
}

char	*ft_skip_spaces(char *inpt)
{
	while (*inpt != '\0' && ft_strchr(*inpt, " \t\n\f\v\r"))
			inpt++;
	return (inpt);
}
