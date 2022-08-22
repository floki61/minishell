/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:34:38 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/22 02:11:11 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_args(t_exec **exec, int i, char **ps)
{
	char		**one;
	char		*q;
	int			token;

	token = get_token(ps, &q);
	if (token == 0)
		return (0);
	if (token != 'F')
	{
		printf ("minishell : syntax error unexpected token '%c'\n", token);
		g_global.error = 258;
		return (0);
	}
	one = ft_split(q, ' ', 1);
	(*exec)->args[i] = one[0];
	free_tab(one, 1);
	return (1);
}

static char	*filenames(char *file, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0' && !ft_strchr(str[i], " \t\n\f\v\r")
		&& !ft_strchr(str[i], "|<>"))
	{
		if (str[i] == 1)
		{
			i++;
			while (str[i] && !(str[i] == 1))
				file[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			file[j++] = str[i++];
	}
	file[j] = '\0';
	return (file);
}

char	*clean(char *str)
{
	int		i;
	int		j;
	char	*file;

	i = 0;
	j = 0;
	while (str[i] != '\0' && !ft_strchr(str[i], " \t\n\f\v\r")
		&& ft_strchr(str[i], "|<>"))
	{
		if (str[i] == 1)
		{
			j += 2;
			inside_quotes(str, &i);
		}
		else
			i++;
	}
	file = malloc (sizeof(char) * (i - j + 1));
	return (filenames(file, str));
}

void	ft_skip_spaces(char *inpt, int *i)
{
	while (inpt[(*i)] != '\0' && ft_strchr(inpt[(*i)], " \t\n\f\v\r"))
			(*i)++;
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
