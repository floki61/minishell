/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:36:30 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/21 18:40:31 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*piping(t_cmd *left, t_cmd *right)
{
	t_pipe	*cmd;

	cmd = malloc(sizeof(t_pipe) + 1);
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*redirect(t_cmd	*exe, char *file, int mode, int fd)
{
	t_redir	*cmd;

	cmd = malloc(sizeof(t_redir) + 1);
	cmd->type = REDIR;
	cmd->exe = exe;
	cmd->file = file;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}

t_cmd	*exelior(char *s)
{
	t_exec	*cmd;
	int		i;
	int		words;

	i = 0;
	words = wd_count(s, ' ', 1);
	cmd = malloc (sizeof(t_exec) + 1);
	cmd->args = malloc (sizeof(char *) * (words + 1));
	cmd->type = EXEC;
	while (i < words)
	{
		cmd->args[i] = 0;
		i++;
	}
	cmd->args[i] = 0;
	return ((t_cmd *)cmd);
}

static int	free_exe(t_cmd *cmd)
{
	int		i;
	t_exec	*exe;

	i = 0;
	exe = (t_exec *)cmd;
	if (g_exit_status == 7)
		i++;
	free_tab(exe->args, i);
	free (exe);
	return (0);
}

void	free_struct(t_cmd *cmd)
{
	t_redir	*red;
	t_pipe	*pip;

	if (cmd == 0)
		return ;
	if (cmd->type == EXEC)
		free_exe(cmd);
	else if (cmd->type == PIPE)
	{
		pip = (t_pipe *)cmd;
		free_struct(pip->left);
		free_struct(pip->right);
		free (pip);
	}
	else if (cmd->type == REDIR)
	{
		red = (t_redir *)cmd;
		free (red->file);
		free_struct(red->exe);
		free (red);
	}
}
