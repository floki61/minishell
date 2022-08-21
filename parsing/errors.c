/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:01:44 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/21 20:02:55 by sfarhan          ###   ########.fr       */
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

t_cmd	*parser(char **ps, t_list **env, t_quote *quote, int *i)
{
	t_exec		*exec;
	t_cmd		*cmd;

	cmd = exelior(*ps);
	exec = (t_exec *)cmd;
	cmd = parsered (cmd, ps, env, quote);
	if (cmd == 0)
		return (0);
	while (!exist(ps, "|"))
	{
		if (cmd == 0)
			return (0);
		if (exec_args(&exec, (*i), ps) == 0)
			break ;
		exec->args[(*i)] = if_dsigne(exec->args[(*i)], env, quote);
		(*i)++;
		cmd = parsered (cmd, ps, env, quote);
		if (cmd == 0)
			return (0);
	}
	return (cmd);
}
