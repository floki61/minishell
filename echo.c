/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 04:34:11 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/11 14:53:03 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echoprint(char **cmd, int i)
{
	char *line;
	int n;

	n = i;
	line = NULL;
	if (!cmd[i])
		return(1);
	while (cmd[i])
	{	
		line = ft_strjoin(line, cmd[i]);
		if(cmd[++i])
			line = ft_strjoin(line, " ");
	}
	printf ("%s", line);
	if (n == 1)
		printf("\n");
	return (1);
}

int	ft_echo(char **cmd)
{
	int i;
	int n;

	i = 1;
	while(cmd[i])
	{
		n = 0;
		if(n == 0)
		{
			if(cmd[i][n] != '-')
			{
				if(echoprint(cmd, i))
					return (2);
			}
			else
				n++;
		}
		while(cmd[i][n] == 'n')
			n++;
		if(ft_strlen(cmd[i]) == n)
			i++;
		else
			if(echoprint(cmd, i))
				return (2);
	}
	echoprint(cmd, i);
	return (2);
}

int	spaces_still(char *str)
{
	int	i;
	int	spaces;
	
	i = 0;
	spaces = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			spaces++;
		i++;
	}
	return (spaces);
}