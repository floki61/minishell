/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:53 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/22 01:45:47 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_c(int sig)
{
	if (sig == 2)
	{
		printf ("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.exit = 1;
	}
}

void	handle_exit(char *buf)
{
	if (buf == NULL)
	{
		printf ("exit\n");
		exit (g_global.exit);
	}
}

static void	init_tools(t_tool *tools, char **envp)
{
	tools->fd = 0;
	tools->envp = envp;
	tools->limiter = NULL;
	tools->in = 0;
	tools->out = 0;
	tools->free = 25;
	tools->stdin_copy = dup(STDIN_FILENO);
	tools->stdout_copy = dup(STDOUT_FILENO);
}

void	execution(t_cmd *cmd, t_list **data, t_tool tools)
{
	pid_t	pid;
	int		wait_status;

	pid = fork();
	if (pid == 0)
	{
		signal (SIGINT, SIG_DFL);
		signal (SIGQUIT, SIG_DFL);
		run_cmd(cmd, &tools, data);
	}
	signal(SIGINT, SIG_IGN);
	free_struct(cmd);
	waitpid(pid, &wait_status, 0);
	if (g_global.error == 258 || g_global.error == 1)
	{
		g_global.exit = g_global.error;
		g_global.error = 0;
	}
	else if (WIFSIGNALED(wait_status))
		g_global.exit = WTERMSIG(wait_status) + 128;
	else
		g_global.exit = WEXITSTATUS(wait_status);
	signal(SIGINT, handle_c);
	if (access("/tmp/ ", F_OK) != -1)
		unlink("/tmp/ ");
}

int	main(int ac, char **av, char **envp)
{
	char	*buf;
	t_list	*data;
	t_tool	tools;
	t_cmd	*cmd;

	data = NULL;
	(void) ac;
	(void) av;
	init_tools(&tools, envp);
	ft_envp(envp, &data);
	while (1)
	{
		signal (SIGINT, handle_c);
		signal (SIGQUIT, SIG_IGN);
		buf = readline("minishell-$ ");
		handle_exit(buf);
		add_history(buf);
		cmd = parsecmd(buf, &data);
		if (ifexit(cmd) || ifenv(cmd, &data))
			free_struct(cmd);
		else
			execution (cmd, &data, tools);
		free (buf);
	}
	return (0);
}
