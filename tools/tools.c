/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:34:38 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/18 21:31:44 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_args(t_exec **exec, int i, char **ps)
{
	char		**one;
	char		*q;
	int			token;

	token = get_token(ps, &q);
	if (token == 0)
		return (0);
	if (token != 'F')
	{
		printf ("minishell : syntax error unexpected token '%c'\n", token);
		return (0);
	}
	one = ft_split(q, ' ', 1);
	(*exec)->args[i] = one[0];
	free_tab(one, 1);
	return (1);
}

static char	*filenames(char *file, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0' && !ft_strchr(str[i], " \t\n\f\v\r")
		&& !ft_strchr(str[i], "|<>"))
	{
		if (str[i] == 1)
		{
			i++;
			while (str[i] && !(str[i] == 1))
				file[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			file[j++] = str[i++];
	}
	file[j] = '\0';
	return (file);
}

char	*clean(char *str)
{
	int		i;
	int		j;
	char	*file;

	i = 0;
	j = 0;
	while (str[i] != '\0' && !ft_strchr(str[i], " \t\n\f\v\r")
		&& ft_strchr(str[i], "|<>"))
	{
		if (str[i] == 1)
		{
			j += 2;
			inside_quotes(str, &i);
		}
		else
			i++;
	}
	file = malloc (sizeof(char) * (i - j + 1));
	return (filenames(file, str));
}

void	ft_skip_spaces(char *inpt, int *i)
{
	while (inpt[(*i)] != '\0' && ft_strchr(inpt[(*i)], " \t\n\f\v\r"))
			(*i)++;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
