/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:02:03 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/20 23:51:39 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **path, int i)
{
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free (path);
}

static int	measure(char *line, int i, int *count)
{
	char	quote;

	if (ft_strchr(line[0], "<>") == 1)
	{
		if (ft_limites(&line[i]) == 2 && line[i + 2] != ' ')
			(*count)++;
		else if (ft_limites(&line[i]) == 1 && line[i + 1] != ' ')
			(*count)++;
		while (line[i] && ft_strchr(line[i], "<>"))
			i++;
	}
	if (line[i] == 34 || line[i] == 39)
	{
		quote = line[i];
		i++;
		while (line[i] && !(line[i] == quote && ft_strchr(line[i + 1], "|<> ")))
			i++;
		if (line[i])
			i++;
	}
	return (i);
}

static int	spaces_needed(char *line, int i, int *count)
{
	if (ft_limites(&line[i]) == 1)
	{
		if (line[i - 1] != ' ')
			(*count)++;
		if (line[i + 1] != ' ')
			(*count)++;
	}
	else if (ft_limites(&line[i]) == 2)
	{
		if (line[i - 1] != ' ' && line[i - 1] != '|')
			(*count)++;
		if (line[i + 2] != ' ')
			(*count)++;
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
		if ((i == 0 && ft_strchr(line[i], "<>") == 1)
			|| line[i] == 34 || line[i] == 39)
			i = measure(line, i, &count);
		if (ft_strchr(line[i], "|<>"))
			i = spaces_needed(line, i, &count);
		if (line[i])
			i++;
	}
	if (count > 0)
	{
		str = malloc(sizeof(char) * (ft_strlen(line) + (count) + 1));
		return (corrected(line, str));
	}
	return (line);
}
