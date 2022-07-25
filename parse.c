/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:37:56 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/25 04:23:25 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		token;
	char	quote[1];

	quote[0] = 1;
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
	if (*s == 1)
	{
		s++;
		while (s < es && !ft_strchr(*s, quote))
			s++;
		s++;
	}
	else
	{
		while (s < es && !ft_strchr(*s, " \t\n\f\v\r") && !ft_strchr(*s, "|<>") && !ft_strchr(*s, quote))
			s++;
	}
	if (eq)
	{
		*eq = s;
	}
	while (s < es && ft_strchr(*s, " \t\n\f\v\r"))
		s++;
	*ps = s;
	//printf ("%s || %s\n", *ps, s);
	return (token);
}

t_cmd	*parseexec(char **ps, char *es, char **env, t_quote quote)
{
	t_exec	*exec;
	char	*q;
	char	*eq;
	char	**one;
	int		token;
	int		i;
	int		words;
	t_cmd	*cmd;

	i = 0;
	words = wd_count(*ps, ' ', 1);
	cmd = exelior(*ps);
	exec = (t_exec *)cmd;
	cmd = parsered (cmd, ps, es);
	while (!exist(ps, es, "|"))
	{
		if ((token = get_token(ps, es, &q, &eq)) == 0)
			break ;
		if (token != 'F')
		{
			printf ("Errorr %d\n", i);
			exit (1);
		}
		one = ft_split(q, ' ', 1);
		exec->args[i] = one[0];
		if (quote.quote != 2 && if_dsigne(exec->args[i], env) != 0)
			exec->args[i] = if_dsigne(exec->args[i], env);
		//printf ("exe[%d] = %s\n", i, exec->args[i]);
		i++;
		if (i > words)
			exit (1);
		cmd = parsered (cmd, ps, es);
	}
	return (cmd);
}

t_cmd	*parsecmd(char *str, char **env)
{
	char	*es;
	t_cmd	*cmd;
	t_quote	quote;

	es = NULL;
	if (str[0] == '|')
	{
		printf ("minishell: syntax error near unexpected token '|'\n");
		exit (1);
	}
	str = quotes(str, &quote);
	//add redirection rules in ft_path
	//str = ft_path(str);
	es = str + ft_strlen(str);
	cmd = parsepipe(&str, es, env, quote);
	//exist (&str, es, "");
	if (str != es)
	{
		printf ("Errori\n");
		exit (1);
	}
	return (cmd);
}

t_cmd	*parsepipe(char	**ps, char *es, char **env, t_quote quote)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, es, env, quote);
	if (exist(ps, es, "|"))
	{
		get_token(ps, es, 0, 0);
		cmd = piping(cmd, parsepipe(ps, es, env, quote));
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
			printf ("Error missing file\n");
			exit (1);
		}
		clear = clean(q);
		if (token == '<')
			cmd = redirect(cmd, clear, O_RDONLY, 0, 1);
		else if (token == '>')
			cmd = redirect(cmd, clear, O_WRONLY | O_CREAT | O_TRUNC, 1, 2);
		else if (token == '+')
			cmd = redirect (cmd, clear, O_WRONLY | O_CREAT | O_APPEND, 1, 3);
		else if (token == '-')
			cmd = redirect (cmd, clear, O_RDONLY, 0, 4);
		cmd = parsered(cmd, ps, es);
	}
	return (cmd);
}
