/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:37:56 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/08 18:00:14 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token(char **ps, char **q)
{
	char	*s;
	int		i;
	int		token;

	i = 0;
	s = *ps;
	while (s[i] != '\0' && ft_strchr(s[i], " \t\r\n\v\f"))
		i++;
	if (q)
		*q = &s[i];
	token = s[i];
	if (s[i] == 0)
		return (token);
	else if (s[i] == '|')
	{
		i++;
		token = '|';
	}
	else if (s[i] == '<' || s[i] == '>')
		token = followed(&s);
	else
		token = 'F';
	if (s[i] == 1)
	{
		i++;
		while (s[i] && !((s[i] == 1 && s[i + 1] == ' ')))
			i++;
		if (s[i])
			i++;
	}
	else
	{
		while (s[i] != '\0' && !ft_strchr(s[i], " \t\r\n\v\f") && !ft_strchr(s[i], "|<>") && s[i] != 1)
			i++;
	}
	while (s[i] != '\0' && ft_strchr(s[i], " \t\r\n\v\f"))
		i++;
	*ps = &s[i];
	//printf ("ps =%s\ns =%s\nq =%s\n", *ps, &s[i], *q);
	return (token);
}

t_cmd	*parseexec(char **ps, t_list **env, t_quote quote)
{
	t_exec	*exec;
	char	*q;
	char	**one;
	int		token;
	int		i;
	int		x;
	t_cmd	*cmd;

	i = 0;
	x = 0;
	cmd = exelior(*ps);
	exec = (t_exec *)cmd;
	//printf ("the cmd : %s\nthe words = %d\n", *ps, words);
	cmd = parsered (cmd, ps,quote);
	while (!exist(ps, "|"))
	{
		if ((token = get_token(ps, &q)) == 0)
			break ;
		if (token != 'F')
		{
			printf ("%d\n", i);
			exit (1);
		}
		//for quotes its cuz of the inprintable char 1
		one = ft_split(q, ' ', 1);
		exec->args[i] = one[0];
		//printf ("exe[%d] = %s with %d for %d quote\n", i, exec->args[i], quote.quote[x], x);
		//if (quote.quote[x] == 1 && ft_skip(exec->args[i], "$"))
		//{
			exec->args[i] = if_dsigne(exec->args[i], env, quote, &x);
			//printf ("after exe[%d] = %s|\n", i, exec->args[i]);
		//}
		//else
			//exec->args[i] = no_space(exec->args[i]);
		//x++;
		i++;
		// if (i > words)
		// 	exit (1);
		cmd = parsered (cmd, ps,quote);
	}
	return (cmd);
}

t_cmd	*parsecmd(char *str, t_list **env)
{
	int		x;
	int		words;
	t_cmd	*cmd;
	t_quote	quote;

	x = 0;
	words = num_quotes(str, ' ');
	quote.quote = malloc(sizeof(int) * words + 1);
	while (x < words)
	{
		quote.quote[x] = 1;
		x++;
	}
	quote.quote[x] = 0;
	if (str[0] == '|')
	{
		printf ("minishell: syntax error near unexpected token '|'\n");
		exit (1);
	}
	str = quotes(str, &quote);
	str = ft_path(str);
	cmd = parsepipe(&str, env, quote);
	return (cmd);
}

t_cmd	*parsepipe(char	**ps, t_list **env, t_quote quote)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, env, quote);
	if (exist(ps, "|"))
	{
		get_token(ps, 0);
		cmd = piping(cmd, parsepipe(ps, env, quote));
	}
	return (cmd);
}

t_cmd	*parsered(t_cmd	*cmd, char **ps,t_quote quote)
{
	int		token;
	char	*q;
	char	*clear;

	while (exist(ps, "<>"))
	{
		token = get_token(ps, 0);
		if (get_token(ps, &q) != 'F')
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
		cmd = parsered(cmd, ps, quote);
	}
	return (cmd);
}
