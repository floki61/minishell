/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:54:07 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/18 23:14:52 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	followed(char *s, int *i)
{
	int		token;

	if (s[(*i)] == '<')
	{
		token = '<';
		(*i)++;
		if (s[(*i)] == '<')
		{
			(*i)++;
			token = '-';
		}
		return (token);
	}
	else if (s[(*i)] == '>')
	{
		token = '>';
		(*i)++;
		if (s[(*i)] == '>')
		{
			(*i)++;
			token = '+';
		}
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

static char	*get_cmd(t_exec *exe, char *path)
{
	int		j;
	char	**cmd;

	j = -1;
	cmd = ft_splito(path, ':');
	if (access(exe->args[0], F_OK | X_OK) != -1)
		return (exe->args[0]);
	while (cmd[++j])
	{
		cmd[j] = ft_strjoin(cmd[j], "/");
		cmd[j] = ft_strjoin(cmd[j], exe->args[0]);
		if (ft_strcmp(cmd[j], "/usr/local/bin/") == 0)
			break ;
		if (access(cmd[j], F_OK | X_OK) != -1)
			return (cmd[j]);
	}
	fperror(exe->args[0], ": command not found\n");
	if (cmd && cmd[j] && ft_strcmp(cmd[j], "/usr/local/bin/") != 0)
		free (exe->args[0]);
	exit (127);
}

char	*get_path(t_exec *exe, t_list **data)
{
	t_list	*tmp;

	tmp = *data;
	while (tmp)
	{
		if (tmp->name[0] == 'P')
		{
			if (ft_strncmp(tmp->name, "PATH", 4) == 0)
				return (get_cmd(exe, tmp->value));
		}
		tmp = tmp->next;
	}
	fperror(exe->args[0], ": No such file or directory\n");
	return (NULL);
}

void	run_cmd(t_cmd *cmd, t_tool *tools, t_list **data)
{
	if (cmd == 0)
		exit (255);
	if (cmd->type == EXEC)
		type_exec(cmd, tools, data);
	else if (cmd->type == PIPE)
		type_pipe(cmd, tools, data);
	else if (cmd->type == REDIR)
		type_redir(cmd, tools, data);
}
