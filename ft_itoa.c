/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 05:22:46 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/11 12:38:24 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count(long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = n * -1;
		count++;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

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

char	*ft_itoa(int n)
{
	int			i;
	char		*str;
	long int	nb;

	if (n == 0)
		return (ft_strdup("0"));
	i = count(n);
	str = (char *) malloc(sizeof(char) * (i + 1));
	if (!(str))
		return (0);
	str[i] = '\0';
	i--;
	nb = n;
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		str[i] = '0' + (nb % 10);
		nb = nb / 10;
		i--;
	}
	return (str);
}
