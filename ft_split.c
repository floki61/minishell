/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:49 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/08 11:02:55 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wd_count(const char *str, char c, int access)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == 1 && access == 1)
		{
			i++;
			while (str[i] != '\0' && !((str[i] == 1 && str[i + 1] == ' ')))
				i++;
			if (str[i])
				i++;
			len++;
		}
		while (str[i] == c)
			i++;
		if (str[i] != '\0' && str[i] != c && str[i] != 1)
		{
			while (str[i] != '\0' && str[i] != c)
				i++;
			len++;
		}
	}
	return (len);
}

static int	ft_test(const char *str, int i, char c, int access)
{
	int		cnt;
	char	*s;

	s = (char *)str;
	cnt = 0;
	if (s[i] == 1 && access == 1)
	{
		i++;
		while (s[i] && !((s[i] == 1 && s[i + 1] == ' ')))
		{
			i++;
			cnt++;
		}
		if (s[i])
			i++;
	}
	else
	{
		while (s[i] && (s[i] != c))
		{
			i++;
			cnt++;
		}
	}
	return (i);
}

static char	*copy(int t, char const *s, char c, int access)
{
	int		j;
	int		len ;
	char	*str;

	j = 0;
	len = ft_test(s, t, c, access);
	str = (char *)malloc(sizeof (char) * len + 1);
	if (!str)
		return (NULL);
	if (s[t] == 1 && access == 1)
	{
		if (s[t] && s[t] == 1)
			t++;
		while (j < len && !((s[t] == 1 && s[t + 1] == ' ')))
		{
			str[j] = (char)s[t];
			j++;
			t++;
		}
		if (s[t])
			t++;
	}
	else
	{
		while (j < len && (s[t] != c))
		{
			str[j] = (char)s[t];
			j++;
			t++;
		}
	}
	str[j] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c, int access)
{
	int		i;
	int		j;
	int		words;
	char	**tab;

	tab = NULL;
	i = 0;
	j = 0;
	words = wd_count(s, c, access);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	while (j < words)
	{
		while (s[i] == c)
			i++;
		tab[j] = copy(i, s, c, access);
		i = ft_test(s, i, c, access);
		j++;
	}
	tab[j] = 0;
	return (tab);
}
