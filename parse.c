/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:37:56 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/05 18:28:37 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token(char **ps, char *es, char **q, char **eq)
{
	char	*s = NULL;
	int		token;

	s = *ps;
	while (s < es && ft_strchr(*s, " \t\n\f\v\r"))
		s++;
	if (q)
		*q = s;
	token = *s;
	if (*s == 0)
		return (token);
	else if (*s == '|')
	{
		s++;
		token = '|';
	}
	else if (*s == '<' || *s == '>')
		token = followed(&s);
	else
		token = 'F';
	while (s < es && !ft_strchr(*s, " \t\n\f\v\r") && !ft_strchr(*s, "|<>"))
		s++;
	if (eq)
	{
		*eq = s;
	}
	while (s < es && ft_strchr(*s, " \t\n\f\v\r"))
		s++;
	*ps = s;
	return (token);
}

t_cmd	*parseexec(char **ps, char *es)
{
	t_exec	*exec;
	char	*q, *eq;
	char	**two, **one;
	int		token , i, j;
	t_cmd	*cmd;

	i = 0;
	j = 0;
	cmd = exelior();
	exec = (t_exec*)cmd;
	while (!exist(ps, es, "|"))
	{
		cmd = parsered (cmd, ps ,es);
		if ((token = get_token(ps, es, &q, &eq)) == 0)
			break;
		if (token != 'F')
		{
			printf ("Error\n");
			exit (1);
		}
		if (ft_skip(q, "|") && i == 0)
		{
			two = ft_split(q, '|');
			while (two[i])
			{
				exec->args[i] = two[i];
				i++;
			}
			i = 0;
		}
		else if (ft_skip(q, "<>") && i == 0)
		{
			if (ft_skip(q, ">"))
				one = ft_split(q, '>');
			else if (ft_skip(q, "<"))
				one = ft_split(q, '<');
			while (one[i])
			{
				exec->args[i] = one[i];
				i++;
			}
			i = 0;
		}
		else if (i == 0)
		{
			exec->args[i] = q;
			exec->erags[i] = 0;
		}
		i++;
		if (i >= 10)
			exit (1);
		cmd = parsered (cmd, ps, es);
	}
	exec->args[i] = 0;
	exec->erags[i] = 0;
	return (cmd);
}

t_cmd	*parsecmd(char *str)
{
	char	*es = NULL;
	t_cmd	*cmd;

	if (str[0] == '|')
	{
		printf ("minishell: syntax error near unexpected token '|'\n");
		exit (1);
	}
	str = ft_path(str);
	es = str + ft_strlen(str);
	cmd = parsepipe(&str, es);
	//exist (&str, es, "");
	if (str != es)
	{
		printf ("Error\n");
		exit (1);
	}
	//end_it(cmd);
	return (cmd);
}

t_cmd	*parsepipe(char	**ps, char *es)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, es);
	if (exist(ps, es, "|"))
	{
		get_token(ps, es, 0, 0);
		cmd = piping(cmd, parsepipe(ps, es));
	}
	return (cmd);
}

t_cmd	*parsered(t_cmd	*cmd, char **ps, char *es)
{
	int		token;
	char	*q;
	char	*eq;
	char	*clear;

	while (exist(ps, es, "<>"))
	{
		token = get_token(ps, es, 0, 0);
		if (get_token(ps, es, &q, &eq) != 'F')
		{
			printf ("Error\n");
			exit (1);
		}
		clear = clean(q);
		if (token == '<')
		{
			cmd = redirect(cmd, clear, O_RDONLY, 0);
			break;
		}
		else if (token == '>')
		{
			cmd = redirect(cmd, clear, O_WRONLY | O_CREAT | O_TRUNC, 1);
			break;
		}
		else if (token == '+')
		{
			cmd = redirect (cmd, clear, O_WRONLY | O_CREAT | O_APPEND, 1);
			break;
		}
		else if (token == '-')
		{
			cmd = redirect (cmd, clear, 0, 0);
			break;
		}
	}
	return (cmd);
}
