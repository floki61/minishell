/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:46:27 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/08 18:49:32 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	three_steps(char *line, char *str, int *x, int *y)
{
	int	i;
	int	j;

	i = *x;
	j = *y;
	if (line[i - 1] != ' ')
	{
		str[j] = ' ';
		j++;
	}
	str[j] = line[i];
	str[j + 1] = ' ';
	if (line[i + 1] == ' ')
		i++;
	*x = i + 1;
	*y = j + 2;
}

static void	four_steps(char *line, char *str, int *x, int *y)
{
	int	i;
	int	j;

	i = *x;
	j = *y;
	if (line[i - 1] != ' ' && str[j - 1] != ' ')
	{
		str[j] = ' ';
		j++;
	}
	str[j] = line[i];
	str[j + 1] = line[i];
	str[j + 2] = ' ';
	if (line[i + 2] == ' ')
		i++;
	*x = i + 2;
	*y = j + 3;
}

static void	start_line(char *line, char *str, int *x, int *y)
{
	int	i;
	int	j;

	i = *x;
	j = *y;
	if (ft_limites(&line[i]) == 1 && line[i + 1] != ' ')
	{
		str[j] = line[i];
		str[j + 1] = ' ';
		*x = i + 1;
		*y = j + 2;
	}
	else if (ft_limites(&line[i]) == 2 && line[i + 2] != ' ')
	{
		str[j] = line[i];
		str[j + 1] = line[i + 1];
		str[j + 2] = ' ';
		*x = i + 2;
		*y = j + 3;
	}
}

static void	inside(char *line, char *str, int *x, int *y)
{
	int	i;
	int	j;

	i = *x;
	j = *y;
	if (line[i] == 1)
	{
		str[j] = line[i];
		i++;
		j++;
		while (line[i] && !(line[i] == 1 && ft_strchr(line[i + 1], "|<>")))
		{
			str[j] = line[i];
			i++;
			j++;
		}
		if (line[i])
		{
			str[j] = line[i];
			i++;
			j++;
		}
	}
	*x = i;
	*y = j;
}

char	*corrected(char *line, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (i == 0 && ft_strchr(line[i], "<>"))
			start_line(line, str, &i, &j);
		inside(line, str, &i, &j);
		if (ft_strchr(line[i], "|<>"))
		{
			if (ft_limites(&line[i]) == 1)
				three_steps(line, str, &i, &j);
			if (ft_limites(&line[i]) == 2)
				four_steps(line, str, &i, &j);
		}
		else
			str[j++] = line[i++];
	}
	str[j] = '\0';
	free (line);
	return (str);
}
