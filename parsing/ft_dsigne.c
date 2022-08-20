/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsigne.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 23:44:48 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/18 21:01:18 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		(*dollar) = 0;
	}
}

char	**cashier(char *str)
{
	char	**words;
	int		i;
	int		j;
	int		dollar;

	i = 0;
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
	free (str);
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
		quote[len++] = str[i++];
	quote[len] = '\0';
	return (quote);
}
