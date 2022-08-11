/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsigne.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 23:44:48 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/08 18:04:36 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**forenv(char **env)
// {
// 	int		i;
// 	char	**op;
// 	char	**operation;

// 	i = 0;
// 	while (env[i])
// 		i++;
// 	operation = malloc(sizeof(char *) * (i + 1));
// 	i = 0;
// 	while (env[i])
// 	{
// 		op = ft_split(env[i], '=', 0);
// 		operation[i] = op[0];
// 		i++;
// 	}
// 	operation[i] = 0;
// 	return (operation);
// }

// char	*exdsigne(char *op, t_list **env)
// {
// 	t_list *tmp;

// 	i = 0;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(op, tmp->name) == 0)
// 			return (tmp->value);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

void	accountant(char **str, int i, int *dollar)
{
	char	*s;

	s = *str;
	if ((*dollar) % 2 == 0)
	{
		while ((*dollar))
		{
			s[i - (*dollar)] = 2;
			(*dollar)--;
		}
	}
	else
	{
		while ((*dollar) > 1)
		{
			s[i - (*dollar)] = 2;
			(*dollar)--;
		}
		(*dollar) = 0;
	}
}

char	**cashier(char *str)
{
	char	**words;
	int		i;
	int		j;
	int		dollar;

	i = 0;
	j = 0;
	dollar = 0;
	words = ft_splito(str, 1);
	while (words[i])
	{
		j = 0;
		while (words[i][j])
		{
			while (words[i][j] == '$')
			{
				dollar++;
				j++;
			}
			accountant(&words[i], j, &dollar);
			j++;
		}
		i++;
	}
	return (words);
}

char	*after_world(char *str)
{
	int		i;
	int		len;
	char	*quote;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39 || str[i] == ' ')
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (NULL);
	len = ft_strlen(str) - i;
	quote = malloc (sizeof(char) * (len + 1));
	len = 0;
	while (str[i])
	{
		quote[len] = str[i];
		i++;
		len++;
	}
	quote[len] = '\0';
	return (quote);
}
