/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 12:36:30 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/04 22:57:44 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*piping(t_cmd *left, t_cmd *right)
{
	t_pipe	*cmd;

	cmd = malloc(sizeof(t_pipe) + 1);
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd*)cmd);
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
	return ((t_cmd*)cmd);
}

t_cmd	*exelior()
{
	t_exec	*cmd;
	cmd = malloc (sizeof(t_exec) + 1);
	cmd->type = EXEC;
	return ((t_cmd*)cmd);
}

int	ft_strchr(char s, char *scan)
{
	int	i;

	i = 0;
	while (scan[i] && scan[i] != s)
		i++;
	if (i == ft_strlen(scan))
		return (0);
	return (1);
}

int	ft_skip(char *s, char *skip)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (skip[j])
		{
			if (skip[j] == s[i])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	exist(char **ps, char *es, char *token)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(*s, " \t\n\v\f\r"))
		s++;
		*ps = s;
	return *s && ft_strchr(*s, token);
}