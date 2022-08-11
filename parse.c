/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:37:56 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/11 15:54:56 by sfarhan          ###   ########.fr       */
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
	ft_skip_spaces(s, &i);
	if (q)
		*q = &s[i];
	token = tokenizer(s, &i);
	if (s[i] == 1)
	{
		i++;
		while (s[i] && !((s[i] == 1 && s[i + 1] == ' ')))
			i++;
		if (s[i])
			i++;
	}
	else
		while (s[i] != '\0' && !ft_strchr(s[i], " \t\r\n\v\f")
			&& !ft_strchr(s[i], "|<>"))
			i++;
	ft_skip_spaces(s, &i);
	*ps = &s[i];
	return (token);
}

t_cmd	*parseexec(char **ps, t_list **env, t_quote quote)
{
	t_exec	*exec;
	int		x;
	int		i;
	t_cmd	*cmd;

	i = 0;
	x = 0;
	cmd = exelior(*ps);
	exec = (t_exec *)cmd;
	cmd = parsered (cmd, ps, env, quote);
	while (!exist(ps, "|"))
	{
		if (exec_args(&exec, i, ps) == 0)
			break ;
		exec->args[i] = if_dsigne(exec->args[i], env, quote, &x);
		i++;
		cmd = parsered (cmd, ps, env, quote);
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
		exit (0);
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

t_cmd	*parsered(t_cmd	*cmd, char **ps, t_list **env, t_quote quote)
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
			cmd = redirect(cmd, clear, O_RDONLY, 0);
		else if (token == '>')
			cmd = redirect(cmd, clear, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (token == '+')
			cmd = redirect (cmd, clear, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (token == '-')
			cmd = redirect (cmd, clear, 3, 0);
		cmd = parsered(cmd, ps, env, quote);
	}
	return (cmd);
}
