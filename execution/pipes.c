/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 23:59:14 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/30 08:25:01 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	right_pipe(t_pipe *pip, t_tool *tools, t_list **data, int *p)
{
	if (pip->left->type == REDIR)
		wait(0);
	dup2(p[0], STDIN_FILENO);
	close(p[0]);
	close(p[1]);
	run_cmd(pip->right, tools, data);
	if (pip->right->type == EXEC)
		exit (1);
}

static void	left_pipe(t_pipe *pip, t_tool *tools, t_list **data, int *p)
{
	dup2(p[1], STDOUT_FILENO);
	close(p[0]);
	close(p[1]);
	run_cmd(pip->left, tools, data);
	if (pip->left->type == EXEC)
		exit (1);
}

void	type_pipe(t_cmd *cmd, t_tool *tools, t_list **data)
{
	int		p[2];
	int		wait_status;
	int		pid1;
	int		pid2;
	t_pipe	*pip;

	pip = (t_pipe *)cmd;
	if (pipe(p) == -1)
	{
		printf ("An error occured in the pipe function\n");
		exit (1);
	}
	pid1 = fork();
	if (pid1 == 0)
		left_pipe(pip, tools, data, p);
	pid2 = fork();
	if (pid2 == 0)
		right_pipe(pip, tools, data, p);
	close (p[0]);
	close (p[1]);
	waitpid(pid2, &wait_status, 0);
	waitpid(pid1, &wait_status, 0);
	g_global.exit = WEXITSTATUS(wait_status);
	exit (g_global.exit);
}
