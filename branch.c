/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:02:59 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/11 14:53:27 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	type_pipe(t_cmd *cmd, char **path, t_tool *tools, t_list **data)
{
	int		p[2];
	t_pipe	*pip;

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
		run_cmd(pip->left, path, tools, data);
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
		run_cmd(pip->right, path, tools, data);
		if (pip->right->type == EXEC)
			exit (1);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
}

void	type_exec(t_cmd *cmd, char **path, t_tool *tools, t_list **data)
{
	t_exec	*exe;
	char	*buf;
	char	**end;
	char	*ar;
	int		i;
	int		bult;

	i = 0;
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
	//printf("hello\n");
	buf = get_path(exe, data);
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
					execve(buf, exe->args, tools->envp);
				}
			}
			else
				ft_putstr_fd(ar, tools->fd);
		}
	}
	execve(buf, exe->args, tools->envp);
}

void	type_redir(t_cmd *cmd, char **path, t_tool *tools, t_list **data)
{	
	t_redir	*red;
	t_redir	*red2;

	red = (t_redir *)cmd;
	if (red->mode == 3)
		heredoc(red, tools);
	else
	{
		tools->fd = open(red->file, red->mode, 0644);
		if (tools->fd < 0)
		{
			printf ("Errooor\n");
			exit (1);
		}
		if (tools->c != 1)
		{
			dup2(tools->fd, red->fd);
			if (red->exe->type == REDIR)
			{
				red2 = (t_redir *)red->exe;
				if (red->fd == red2->fd)
					(tools->c) = 1;
			}
		}
		if (red->exe->type == REDIR)
		{
			red2 = (t_redir *)red->exe;
			if (red->fd != red2->fd)
				(tools->c) = 0;
		}
	}
	run_cmd(red->exe, path, tools, data);
}

void	heredoc(t_redir *red, t_tool *tools)
{
	t_exec	*exe;
	char	*ar;
	char	**end;
	int		i;

	i = 0;
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
						exit(1);
					}
				}
				else
					ft_putstr_fd(ar, tools->fd);
			}
		}
	}
}
