/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:44:37 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/10 11:41:50 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	double_quotes(char *str, int *i)
{
	str[(*i)] = 1;
	while (str[(*i)] && str[(*i)] != 34)
		(*i)++;
	if (str[(*i)] == '\0')
	{
		printf ("minishell: quotation error\n");
		exit (1);
	}
	str[(*i)] = 1;
	return (1);
}

static int	single_quotes(char *str, int *i)
{
	str[(*i)] = 1;
	while (str[(*i)] && str[(*i)] != 39)
		(*i)++;
	if (str[(*i)] == '\0')
	{
		printf ("minishell: quotation error\n");
		exit (1);
	}
	str[(*i)] = 1;
	return (2);
}

char	*quotes(char *str, t_quote *quote)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == 34)
			quote->quote[x] = double_quotes(str, &i);
		else if (str[i] == 39)
			quote->quote[x] = single_quotes(str, &i);
		i++;
		if (str[i] == ' ' || str[i] == 34 || str[i] == 39)
		{
			x++;
			if (str[i] == ' ')
				i++;
		}
	}
	return (str);
}
