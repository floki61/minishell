/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:54:07 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/03 12:21:13 by oel-berh         ###   ########.fr       */
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
	int		sign;
	int		len;
	char	*buf;

	i = 0;
	j = 0;
	sign = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$')
			sign = i;
		i++;
	}
	i = 0;
	while (str[i])
	{
		//print until u find the same quote and so on
		//1 means double quote and 2 means single quote
		if (str[i] == 34)
		{
			if (i == 0)
				(quote->start) = 1;
			if (i + 1 <= sign)
				(quote->quote) = 1;
			str[i] = 1;
			//if len == 0 check segv "" | ''
			while (str[i] && str[i] != 34)
			{
				len++;
				i++;
			}
			if (str[i] == '\0')
			{
				printf ("minishell: quotation error\n");
				exit (1);
			}
			str[i] = 1;
			//len++;
		}
		if (str[i] == 39)
		{
			if (i == 0)
				(quote->start) = 1;
			if (i + 1 <= sign)
				(quote->quote) = 2;
			str[i] = 1;
			while (str[i] && str[i] != 39)
			{
				len++;
				i++;
			}
			if (str[i] == '\0')
			{
				printf ("minishell: quotation error\n");
				exit (1);
			}
			if (i + 1 == sign)
				(quote->quote) = 1;
			str[i] = 1;
			//len++;
		}
		i++;
		len++;
	}
	buf = malloc (sizeof(char) * len + 1);
	i = 0;
	while (str[i])
	{
		// if (str[i] == 1)
		// 	i++;
		buf[j] = str[i];
		i++;
		j++;
	}
	buf[j] = '\0';
	//printf ("%d\n", quote->quote);
	//return char allocated with the right size and quote by reference
	return (buf);
}

static char	*get_cmd(t_exec *exe, char *path)
{
	int		j;
	char	**cmd;

	j = -1;
	cmd = ft_split(path, ':', 0);
	if (access(exe->args[0], F_OK) != -1)
		return (exe->args[0]);
	while (cmd[++j])
	{
		cmd[j] = ft_strjoin(cmd[j], "/");
		cmd[j] = ft_strjoin(cmd[j], exe->args[0]);
		if (access(cmd[j], F_OK) != -1)
			return (cmd[j]);
	}
	printf ("minishell: %s: command not found\n", exe->args[0]);
	exit (1);
}

char	*get_path(t_exec *exe, t_list **envp)
{
	t_list	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PATH") == 0)
			return (get_cmd(exe, tmp->value));
		tmp = tmp->next;
	}
	return (0);
}

void	run_cmd(t_cmd *cmd, char **envp, int *c, char **limiter, t_list **data,char **path)
{
	int		fd;
	int		i;
	int		e;
	int		p[2];
	char	*buf;
	char	*ar;
	t_exec	*exe;
	t_pipe	*pip;
	t_redir	*red;
	t_redir	*red2;
	char	**env;

	i = 0;
	ar = NULL;
	env = NULL;
	if (cmd == 0)
		exit (1);
	if (cmd->type == EXEC)
	{
		exe = (t_exec *)cmd;
		if (exe->args[0] == 0)
			exit (1);
		if((e = if_builtins(exe->args, data, path)))
			exit(0) ;
		// i = ft_count(data);
		// env = ft_convert(data, i);
		buf = get_path(exe, data);
		if (*limiter != NULL)
		{
			fd = open("dada", O_RDWR | O_CREAT | O_TRUNC, 0644);
			read_from_0(*limiter, fd);
			dup2(fd, STDIN_FILENO);
			dup2(p[1],STDOUT_FILENO);
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
			//close(1);
			dup2(p[1], STDOUT_FILENO);
			close(p[0]);
			close(p[1]);
			run_cmd(pip->left, envp, c, limiter,data, path);
			exit(0);
		}
		else
		{
			if (pip->left->type == REDIR)
				wait(0);
			//close(0);
			dup2(p[0], STDIN_FILENO);
			close(p[0]);
			close(p[1]);
			run_cmd(pip->right, envp, c, limiter,data, path);
			exit(0);
		}
		close(p[0]);
		close(p[1]);
		// wait(0);
		// wait(0);
	}
	else if (cmd->type == REDIR)
	{
		red = (t_redir *)cmd;
		if (red->token == 4)
		{
			fd = open(0, red->mode);
			limiter = &(red->file);
			exe = (t_exec *)red->exe;
			(*c)++;
			if (exe->args[0] == 0)
			{
				// fd = open(" ", O_RDWR | O_CREAT | O_TRUNC, 0644);
				// while ((ar = get_next_line(0)))
				// {
				// 	if (ft_strncmp(red->file, ar, ft_strlen(red->file)) == 0)
				// 	{
				// 		close(0);
				// 		exit(1) ;
				// 	}
				// 	ft_putstr_fd(ar, fd);
				// }
				// i = 0;
			}
		}
		else
		{
			fd = open(red->file, red->mode, 0644);
			if (fd < 0)
			{
				printf ("Error\n");
				exit (1);
			}
		}
		if (*c == 0)
		{
			dup2(fd, red->fd);
			if (red->exe->type == REDIR)
			{
				red2 = (t_redir *)red->exe;
				if (red->token == red2->token)
					(*c)++;
			}
		}
		run_cmd(red->exe, envp, c, limiter,data, path);
		exit(0);
	}
}

char	*ft_skip_spaces(char *inpt)
{
	while (*inpt != '\0' && ft_strchr(*inpt, " \t\n\f\v\r"))
			inpt++;
	return (inpt);
}
