/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:02:03 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/07 17:01:48 by sfarhan          ###   ########.fr       */
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

static char	*corrected(char *line, char *str)
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
		{
			str[j] = line[i];
			j++;
			i++;
		}
	}
	str[j] = '\0';
	free (line);
	//printf ("line -> '%s'\n", str);
	return (str);
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
