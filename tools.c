/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:34:38 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/09 13:55:09 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizer(char *s, int *x)
{
	int		token;
	int		i;

	i = (*x);
	token = s[i];
	if (s[i] == 0)
		return (token);
	else if (s[i] == '|')
	{
		i++;
		token = '|';
	}
	else if (s[i] == '<' || s[i] == '>')
		token = followed(s, &i);
	else
		token = 'F';
	*x = i;
	return (token);
}

int	num_quotes(const char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] != '\0' && str[i] != 34)
				i++;
			if (str[i])
				i++;
			len++;
		}
		else if (str[i] == 39)
		{
			i++;
			while (str[i] != '\0' && str[i] != 39)
				i++;
			if (str[i])
				i++;
			len++;
		}
		while (str[i] == c)
			i++;
		if (str[i] != '\0' && str[i] != c && str[i] != 39 && str[i] != 34)
		{
			while (str[i] != '\0' && str[i] != c)
				i++;
			len++;
		}
	}
	return (len);
}

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
		printf ("%d\n", i);
		exit (1);
	}
	one = ft_split(q, ' ', 1);
	if (ft_strlen(one[0]) == 0)
		one[0] = " ";
	(*exec)->args[i] = one[0];
	return (1);
}

char	*clean(char *str)
{
	int		i;
	char	*clean;

	i = 0;
	while (str[i] != '\0' && !ft_strchr(str[i], " \t\n\f\v\r"))
		i++;
	clean = malloc (sizeof(char) * i);
	i = 0;
	while (str[i] != '\0' && !ft_strchr(str[i], " \t\n\f\v\r"))
	{
		clean[i] = str[i];
		i++;
	}
	clean[i] = '\0';
	return (clean);
}

void	ft_skip_spaces(char *inpt, int *i)
{
	while (inpt[(*i)] != '\0' && ft_strchr(inpt[(*i)], " \t\n\f\v\r"))
			(*i)++;
}
