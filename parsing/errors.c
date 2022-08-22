/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:01:44 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/22 02:11:02 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_scanner(char *str)
{
	if (str[0] == '|' || ft_strcmp(str, ".") == 0 || ft_strcmp(str, "..") == 0
		|| ft_strcmp(str, "<<") == 0 || ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp (str, ">") == 0)
	{
		printf ("minishell: syntax error near unexpected token\n");
		g_global.error = 258;
		return (0);
	}
	return (1);
}

void	free_tab(char **path, int i)
{
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free (path);
}

t_cmd	*empty_pipe(t_cmd *cmd)
{
	free_struct(cmd);
	printf ("minishell: syntax error near unexpected token\n");
	g_global.error = 258;
	return (0);
}

void	fperror(char *arg, char *error)
{
	write(2, "minishell: ", 11);
	write(2, arg, ft_strlen(arg));
	write(2, error, ft_strlen(error));
}
