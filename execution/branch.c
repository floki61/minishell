/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:02:59 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/30 08:24:53 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	type_exec(t_cmd *cmd, t_tool *tools, t_list **data)
{
	t_exec	*exe;
	char	*buf;
	int		bult;

	buf = NULL;
	exe = (t_exec *)cmd;
	if (exe->args[0] == 0)
		exit (0);
	bult = if_builtins(exe->args, data);
	if (bult)
	{
		if (bult == 2)
			exit (0);
		exit (bult);
	}
	if (tools->limiter != NULL)
		exe_doc(buf, exe, tools, data);
	buf = get_path(exe, data);
	if (buf == NULL)
		exit (127);
	execve(buf, exe->args, tools->envp);
}

static void	multi_red(t_redir *red, t_tool *tools)
{
	if (tools->in != 1 && red->fd == 0)
	{
		dup2(tools->fd, red->fd);
		(tools->in) = 1;
	}
	if (tools->out != 1 && red->fd == 1)
	{
		dup2(tools->fd, red->fd);
		(tools->out) = 1;
	}
}

void	type_redir(t_cmd *cmd, t_tool *tools, t_list **data)
{	
	t_redir	*red;

	red = (t_redir *)cmd;
	if (red->mode == 3)
		heredoc(red, tools);
	else
	{
		tools->fd = open(red->file, red->mode, 0644);
		if (tools->fd < 0)
		{
			tools->fd = should_open(red);
			if (tools->fd == -1)
			{
				fperror (NULL, "Error in opening file descriptor\n");
				exit (1);
			}
		}
		multi_red(red, tools);
	}
	run_cmd(red->exe, tools, data);
}
