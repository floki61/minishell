/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:34:38 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/24 03:20:17 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	much_to_skip(const char *str, int i)
{
	int		cnt;
	char	*s;

	s = (char *)str;
	cnt = 0;
	printf ("much %c , %d\n", s[i], i);
	i++;
	while (s[i] != 1 && s[i])
	{
		i++;
		cnt++;
	}
	i++;
	return (i);
}