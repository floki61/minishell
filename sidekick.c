/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidekick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:12:21 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/21 15:23:48 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	p = NULL;
	while (src[i])
		i++;
	p = malloc((i + 1) * sizeof(char));
	if (!(p))
		return (NULL);
	while (i > 0)
	{
		p[j] = src[j];
		j++;
		i--;
	}
	p[j] = '\0';
	return (p);
}

void	multifiles(char	*str)
{
	int		i;
	int		stock1;
	int		stock2;
	int		count;
	char	**buf;
	char	*first;
	char	*last;

	i = 0;
	count = 0;
	buf = ft_split(str, ' ');
	while (buf[i] && buf[i][0] != '|')
	{
		if (buf[i][0] == '>' || buf[i][0] == '<' && count == 0)
		{
			count++;
			i++;
			stock1 = i;
			first = ft_strdup(str[i]);
		}
		i++;
		if (buf[i] == 0)
		{
			i--;
			stock2 = i;
			last = ft_strdup(buf[i]);
			break ;
		}
	}
	buf[stock1] = last;
	buf[stock2] = first;
	return (buf);
}

// void	multifiles2(char *str)
// {
// 	while (str && *str != '|')
// 	{
// 		if (exist(*str, "", ">"))
// 		{
// 			while (str && ft_strchr(*str, " \n\t\f\r\v") && ft_strchr(*str, ">"))
// 				str++;
// 			while (str && !ft_strchr(*str, " \n\t\f\r\v"))
// 				str++;
// 			multifiles2(str);
// 		}
// 		str++;
// 	}
// 	str--;
// 	while (!ft_strchr(*str, " \n\t\f\r\v"))
// 	{
// 		i++;
// 		str--;
// 	}
// }
