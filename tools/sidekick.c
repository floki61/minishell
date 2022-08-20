/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidekick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:12:21 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/18 21:01:18 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr(char s, char *scan)
{
	int	i;

	i = 0;
	while (scan[i] && scan[i] != s)
		i++;
	if (i == ft_strlen(scan))
		return (0);
	return (1);
}

int	ft_skip(char *s, char *skip)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (skip[j])
		{
			if (skip[j] == s[i])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	exist(char **ps, char *token)
{
	char	*s;
	int		i;

	i = 0;
	s = *ps;
	while (s[i] != '\0' && s[i] == 2)
		s++;
	*ps = &s[i];
	return (s[i] && ft_strchr(s[i], token));
}

int	is_alnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

void	next_quote(char *str, int *i, int *x, int tmp)
{
	if (str[(*i)] == ' ' || str[(*i)] == 34 || str[(*i)] == 39)
	{
		if (tmp + 2 == (*i))
			(*x)--;
		(*x)++;
		if (str[(*i)] == ' ')
			(*i)++;
	}
}
