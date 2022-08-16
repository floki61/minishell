/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:02:03 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/16 03:11:11 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	measure(char *line, int j, int *count)
{
	int	i;

	i = j;
	if (ft_strchr(line[0], "<>") == 1)
	{
		if (ft_limites(&line[i]) == 2 && line[i + 2] != ' ')
			(*count)++;
		else if (ft_limites(&line[i]) == 1 && line[i + 1] != ' ')
			(*count)++;
		while (line[i] && ft_strchr(line[i], "<>"))
			i++;
	}
	if (line[i] == 1)
	{
		i++;
		while (line[i] && !(line[i] == 1 && ft_strchr(line[i + 1], "|<>")))
			i++;
		if (line[i])
			i++;
	}
	return (i);
}

char	*ft_path(char *line)
{
	int		i;
	int		count;
	char	*str;

	i = 0;
	count = 0;
	while (line[i])
	{
		if ((i == 0 && ft_strchr(line[i], "<>") == 1) || line[i] == 1)
			i += measure(line, i, &count);
		if (ft_strchr(line[i], "|<>"))
		{
			if (ft_limites(&line[i]) == 1)
			{
				if (line[i - 1] != ' ')
					count++;
				if (line[i + 1] != ' ')
					count++;
			}
			else if (ft_limites(&line[i]) == 2)
			{
				if (line[i - 1] != ' ' && line[i - 1] != '|')
					count++;
				if (line[i + 2] != ' ')
					count++;
				i++;
			}
		}
		i++;
	}
	if (count > 0)
	{
		str = malloc(sizeof(char) * (ft_strlen(line) + (count * 2)));
		return (corrected(line, str));
	}
	return (line);
}
