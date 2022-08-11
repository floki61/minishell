/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:53 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/11 19:27:16 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	*ft_lastcar(char *str, char c)
{
	int	lent;

	lent = ft_strlen(str);
	while (*str)
		str++;
	while (lent)
	{
		if (*str == c)
		{
			str++;
			return (str);
		}
		lent--;
		str--;
	}
	return (NULL);
}

void	handle_c(int sig)
{
	if (sig == 2)
	{
		printf ("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_d(int sig)
{
	if (sig == 11)
	{
		//rl_replace_line("", 0);
		printf ("exit\n");
		exit(0);
	}
}

void	handle_s(int sig)
{
	if (sig == 3)
		readline ("-> minishell ");
}

int	main(int ac, char **av, char **envp)
{
	int		wait_status;
	char	*buf;
	t_list	*data;
	t_tool	tools;
	t_cmd	*cmd;
	char 	*path;
	pid_t 	pid;

	tools.fd = 0;
	tools.envp = envp;
	tools.limiter = NULL;
	tools.c = 10;
	tools.stdin_copy = dup(STDIN_FILENO);
	tools.stdout_copy = dup(STDOUT_FILENO);
	data = NULL;
	path = NULL;
	(void) ac;
	(void) av;
	signal (SIGINT, handle_c);
	signal (SIGQUIT, handle_s);
	path = getcwd(NULL, 0);
	ft_envp(envp,&data);
	while (1)
	{
		buf = readline("\e[0;31m.ᴍɪɴɪꜱʜᴇʟʟ\e[0m ");
		if (buf == NULL)
			exit(0);
		add_history(buf);
		cmd = parsecmd(buf, &data);
		if(ifexit(cmd) || ifenv(cmd, &data, &path))
			continue;
		else
		{
			pid = fork();
			if (pid == 0)
				run_cmd(cmd, &path, &tools, &data);
			waitpid(pid, &wait_status, 0);
			if(WIFEXITED(wait_status))
				exit_status =  WEXITSTATUS(wait_status);
		}
		//free (buf);
		//system("leaks minishell");
	}
	return (0);
}
