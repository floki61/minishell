/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:37:56 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/03 21:03:25 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token(char **str, char **q, char **eq)
{
	char	*s = NULL;
	int		token;

	s = *str;
	while (*s != '\0' && ft_strchr(*s, " \t\n\f\v\r"))
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
	while (*s != '\0' && !ft_strchr(*s, " \t\n\f\v\r") && !ft_strchr(*s, "|<>"))
		s++;
	if (eq)
	{
		*eq = s;
	}
	while (*s != '\0' && ft_strchr(*s, " \t\n\f\v\r"))
		s++;
	*str = s;
	return (token);
}

t_cmd	*parseexec(char **str)
{
	t_exec	*exec;
	char	*q, *eq;
	char	**two;
	int		token , i;
	t_cmd	*cmd;

	i = 0;
	cmd = exelior();
	exec = (t_exec*)cmd;
	cmd = parsered (cmd, str);
	while (!exist(str, "|"))
	{
		if ((token = get_token(str, &q, &eq)) == 0)
			break;
		if (token != 'F')
		{
			printf ("Error\n");
			exit (1);
		}
		if (ft_skip(q, "|"))
		{
			two = ft_split(q, '|');
			exec->args[i] = two[i];
			exec->erags[i] = two[i];
			//printf ("hello %s, %s\n", two[i], two[i + 1]);
		}
		else
		{
			exec->args[i] = q;
			exec->erags[i] = eq;
		}
		i++;
		if (i >= 10)
			exit (1);
		cmd = parsered (cmd, str);
	}
	exec->args[i] = 0;
	exec->erags[i] = 0;
	return (cmd);
}

t_cmd	*parsecmd(char *str)
{
	t_cmd	*cmd;
	t_exec *exec;

	cmd = parsepipe(&str);
	exist (&str, "");
	exec = (t_exec*)cmd;
	if (*str != '\0')
	{
		printf ("Error1\n");
		exit (1);
	}
	//end_it(cmd);
	return (cmd);
}

t_cmd	*parsepipe(char	**str)
{
	t_cmd	*cmd;

	cmd = parseexec(str);
	if (exist(str, "|"))
	{
		get_token(str, 0, 0);
		cmd = piping(cmd, parsepipe(str));
	}
	return (cmd);
}

t_cmd	*parsered(t_cmd	*cmd, char **str)
{
	int		token;
	char	*q;
	char	*eq;

	while (exist(str, "<>"))
	{
		token = get_token(str, 0, 0);
		if (get_token(str, &q, &eq) != 'F')
		{
			printf ("Erroro\n");
			exit (1);
		}
		if (token == '<')
		{
			cmd = redirect(cmd, q, eq, O_RDONLY, 0);
			break;
		}
		else if (token == '>')
		{
			cmd = redirect(cmd, q, eq, O_WRONLY | O_CREAT | O_TRUNC, 1);
			break;
		}
		else if (token == '+')
		{
			cmd = redirect (cmd, q, eq, O_WRONLY | O_CREAT, 1);
			break;
		}
		else if (token == '-')
		{
			cmd = redirect (cmd, q ,eq , 0, 0);
			break;
		}
	}
	return (cmd);
}
