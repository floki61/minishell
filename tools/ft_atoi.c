/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 05:23:25 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/16 03:32:48 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ftskip(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\f'
		|| str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
	{
		i++;
	}
	return (i);
}

static int	ft_signe(char *str, int i)
{
	unsigned long long	resultat;

	resultat = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10 + (str[i] - '0');
		if (resultat > LLONG_MAX)
			return (-1);
		i++;
	}
	return (resultat);
}

int	ft_atoi(char *str)
{
	int					i;
	int					a;
	unsigned long long	resultat;

	i = ftskip(str);
	a = 1;
	resultat = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			a *= -1;
		i++;
	}
	if (ft_signe(str, i) == -1)
		return (-1);
	else
		resultat = ft_signe(str, i) * a;
	return (resultat);
}
