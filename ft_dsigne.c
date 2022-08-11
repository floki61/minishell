/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsigne.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 23:44:48 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/11 15:09:37 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**forenv(char **env)
{
	int		i;
	char	**op;
	char	**operation;

	i = 0;
	while (env[i])
		i++;
	operation = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		op = ft_split(env[i], '=', 0);
		operation[i] = op[0];
		i++;
	}
	operation[i] = 0;
	return (operation);
}

char	*exdsigne(char *op, char **env)
{
	char	**operation;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(op, env[i], ft_strlen(op)) == 0)
		{
			operation = ft_split(env[i], '=', 0);
			return (operation[1]);
		}
		i++;
	}
	return (0);
}

void	accountant(char **str, int i, int *dollar)
{
	char	*s;

	s = *str;
	if ((*dollar) % 2 == 0)
	{
		while ((*dollar))
		{
			s[i - (*dollar)] = 2;
			(*dollar)--;
		}
	}
	else
	{
		while ((*dollar) > 1)
		{
			s[i - (*dollar)] = 2;
			(*dollar)--;
		}
		if ((*dollar) == 1 && (s[i] == ' ' || s[i] == '\0'))
			s[i - 1] = 3;
		(*dollar) = 0;		// if u found a $ and after there is a space or none make it 3 then if u found 3 make it dollar ;)
	}
}

char	**cashier(char *str)
{
	char	**words;
	int		i;
	int		j;
	int		dollar;

	i = 0;
	j = 0;
	dollar = 0;
	words = ft_splito(str, 1);
	while (words[i])
	{
		j = 0;
		while (words[i][j])
		{
			while (words[i][j] == '$')
			{
				dollar++;
				j++;
			}
			accountant(&words[i], j, &dollar);
			j++;
		}
		i++;
	}
	return (words);
}

char	*after_world(char *str)
{
	int		i;
	int		len;
	char	*quote;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[0] == '?')
			i++;
		if (!is_alnum(str[i]))
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (NULL);
	len = ft_strlen(str) - i;
	quote = malloc (sizeof(char) * (len + 1));
	len = 0;
	while (str[i])
	{
		quote[len] = str[i];
		i++;
		len++;
	}
	quote[len] = '\0';
	return (quote);
}
