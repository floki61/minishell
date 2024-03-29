/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:37:56 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/30 08:25:18 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		inside_quotes(s, &i);
	else
		i = inside_string(s, i);
	ft_skip_spaces(s, &i);
	*ps = &s[i];
	return (token);
}

t_cmd	*parseexec(char **ps, t_list **env, t_quote quote)
{
	int			i;
	static int	memo;
	t_cmd		*cmd;

	i = 0;
	quote.x = memo;
	cmd = parser(ps, env, &quote, &i);
	if (exist(ps, "|"))
		quote.x++;
	if ((i == 0 && ft_strlen(*ps) != 0))
		return (empty_pipe(cmd));
	memo = quote.x;
	if (ft_strlen(*ps) == 0)
		memo = 0;
	return (cmd);
}

t_cmd	*parsecmd(char *str, t_list **env)
{
	int		x;
	int		len;
	int		words;
	t_cmd	*cmd;
	t_quote	quote;

	x = 0;
	quote.x = 0;
	if (error_scanner(str) == 0)
		return (0);
	len = ft_strlen(str);
	str = ft_path(str);
	words = num_quotes(str, ' ');
	quote.quote = malloc(sizeof(int) * words);
	while (x < words)
		quote.quote[x++] = 1;
	str = quotes(str, &quote);
	if (!str)
		return (0);
	cmd = parsepipe(str, env, quote);
	if (len < ft_strlen(str))
		free (str);
	free (quote.quote);
	return (cmd);
}

t_cmd	*parsepipe(char	*ps, t_list **env, t_quote quote)
{
	t_cmd	*cmd;

	cmd = parseexec(&ps, env, quote);
	if (cmd == 0)
		return (0);
	if (exist(&ps, "|"))
	{
		get_token(&ps, 0);
		if (ft_strlen(ps) == 0)
		{
			printf ("minishell: syntax error near unexpected token\n");
			g_global.error = 258;
			return (0);
		}
		cmd = piping(cmd, parsepipe(ps, env, quote));
	}
	return (cmd);
}

t_cmd	*parsered(t_cmd	*cmd, char **ps, t_list **env, t_quote *quote)
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
			g_global.error = 258;
			free_struct(cmd);
			return (0);
		}
		(quote->x)++;
		clear = if_dsigne(clean(q), env, quote);
		cmd = which_redir(cmd, clear, token, q);
		cmd = parsered(cmd, ps, env, quote);
	}
	return (cmd);
}
