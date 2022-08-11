/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:34:38 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/07 17:12:20 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	much_to_skip(const char *str, int i)
{
	int		cnt;
	char	*s;

	s = (char *)str;
	cnt = 0;
	printf ("much %c , %d\n", s[i], i);
	i++;
	while (s[i] != 1 && s[i])
	{
		i++;
		cnt++;
	}
	i++;
	return (i);
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
