/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 04:34:11 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/16 03:17:55 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echoprint(char *str)
{
	if (!str)
		return (1);
	printf("%s", str);
	return (1);
}

char	*join(char **cmd, int i)
{
	char	*str;
	int		j;

	str = NULL;
	j = i;
	while (cmd[i])
	{
		str = ft_strjoin(str, cmd[i]);
		if (cmd[++i])
			str = ft_strjoin(str, " ");
	}
	if (j == 1)
		str = ft_strjoin(str, "\n");
	return (str);
}

char	*skeep_n(char **cmd)
{
	int	i;
	int	n;
	int	p;

	i = 1;
	while (cmd[i])
	{
		n = 0;
		if ((n == 0 && cmd[i][n] != '-') || p == -1)
			return (join(cmd, i));
		n++;
		while (cmd[i][n] == 'n')
			n++;
		if (ft_strlen(cmd[i]) == n)
			i++;
		else
			p = -1;
	}
	return (NULL);
}

int	ft_echo(char **cmd)
{
	if (!cmd[1])
	{
		printf("\n");
		return (2);
	}
	echoprint(skeep_n(cmd));
	return (2);
}
