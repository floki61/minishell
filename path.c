/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:02:03 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/21 15:20:58 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
}

static char	*corrected(char *line, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '|' && (line[i + 1] != ' ' || line[i - 1] != ' '))
		{
			str[j] = ' ';
			str[j + 1] = '|';
			str[j + 2] = ' ';
			i++;
			j += 3;
		}
		str[j] = line[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_path(char *line)
{
	int		i;
	int		size;
	int		count;
	char	*str;

	i = 0;
	count = 0;
	size = ft_strlen(line);
	while (line[i])
	{
		if (line[i] == '|' && (line[i + 1] != ' ' || line[i - 1] != ' '))
			count++;
		i++;
	}
	str = malloc(sizeof(char) * (size + (count * 2)));
	return (corrected(line, str));
}
