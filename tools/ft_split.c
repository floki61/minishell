/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:49 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/18 21:01:18 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_quote(const char *str, int i, char c)
{
	while (str[i] != '\0' && str[i] != c)
	{
		if (str[i] == 1)
		{
			i++;
			while (str[i] && !(str[i] == 1))
				i++;
			if (str[i])
				i++;
		}
		else
			i++;
	}
	return (i);
}

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
			if_quote(str, &i);
			len++;
		}
		while (str[i] == c)
			i++;
		if (str[i] != '\0' && str[i] != c && str[i] != 1)
		{
			i = no_quote(str, i, c);
			len++;
		}
	}
	return (len);
}

static int	ft_test(const char *str, int i, char c, int access)
{
	char	*s;
	int		len;

	len = i;
	s = (char *)str;
	if (s[i] == 1)
		if_quote(str, &i);
	else
	{
		while (s[i] && (s[i] != c))
		{
			if (s[i] == 1)
				i = no_quote(str, i, c);
			else
				i++;
		}
	}
	if (access == 1)
		return (i - len);
	return (i);
}

static char	*copy(int t, char const *s, char c)
{
	int			j;
	int			len;
	char		*str;

	j = 0;
	len = ft_test(s, t, c, 1);
	str = (char *)malloc(sizeof (char) * len + 1);
	if (!str)
		return (NULL);
	while (j < len)
	{
		str[j] = (char)s[t];
		j++;
		t++;
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
		tab[j] = copy(i, s, c);
		i = ft_test(s, i, c, 0);
		j++;
	}
	tab[j] = 0;
	return (tab);
}
