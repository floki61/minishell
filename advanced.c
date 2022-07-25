/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:49 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/22 22:34:20 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count(const char *str, char *buf)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		while (str[i] != '\0' && ft_strchr(str[i], buf))
			i++;
		if (str[i] && !ft_strchr(str[i], buf))
		{
			while (str[i] && !ft_strchr(str[i], buf))
				i++;
			len++;
		}
	}
	return (len);
}

static int	ft_test(const char *str, int i, char *buf)
{
	int		cnt;
	char	*s;

	s = (char *)str;
	cnt = 0;
	while (s[i] && !ft_strchr(s[i], buf))
	{
		i++;
		cnt++;
	}
	return (cnt);
}

static char	*copy(int t, char const *s, char *buf)
{
	int		j;
	int		len ;
	char	*str;

	j = 0;
	len = ft_test(s, t, buf);
	str = (char *)malloc(sizeof (char) * len + 1);
	if (!str)
		return (NULL);
	while (j < len && !ft_strchr(s[t], buf))
	{
		str[j] = (char)s[t];
		j++;
		t++;
	}
	str[j] = '\0';
	return (str);
}

char	**ft_advanced(char const *s, char *buf)
{
	int		i;
	int		j;
	char	**tab;

	tab = NULL;
	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (count(s, buf) + 1));
	if (!tab)
		return (NULL);
	while (j < count(s, buf))
	{
		while (s[i] && ft_strchr(s[i], buf))
			i++;
		tab[j] = copy(i, s, buf);
		i += ft_test(s, i, buf);
		j++;
	}
	tab[j] = 0;
	return (tab);
}
