/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:49 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/01 15:57:34 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count(const char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0' && str[i] != c)
		{
			while (str[i] != '\0' && str[i] != c)
				i++;
			len++;
		}
	}
	return (len);
}

static int	ft_test(const char *str, int i, char c)
{
	int		cnt;
	char	*s;

	s = (char *)str;
	cnt = 0;
	while (s[i] != c && s[i])
	{
		i++;
		cnt++;
	}
	return (cnt);
}

static char	*copy(int t, char const *s, char c)
{
	int		j;
	int		len ;
	char	*str;

	j = 0;
	len = ft_test(s, t, c);
	str = (char *)malloc(sizeof (char) * len + 1);
	if (!str)
		return (NULL);
	while (j < len && s[t] != c)
	{
		str[j] = (char)s[t];
		j++;
		t++;
	}
	str[j] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**tab;

	tab = NULL;
	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (count(s, c) + 1));
	if (!tab)
		return (NULL);
	while (j < count(s, c))
	{
		while (s[i] == c)
			i++;
		tab[j] = copy(i, s, c);
		i += ft_test(s, i, c);
		j++;
	}
	tab[j] = 0;
	return (tab);
}
