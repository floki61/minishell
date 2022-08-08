/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 00:59:24 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/08 12:59:56 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echoprint(char **cmd, int i, t_list **data)
{
	char *line;
	int n;

	n = i;
	line = NULL;
	data = NULL;
	if(!cmd[i])
		return(1);
	while(cmd[i])
	{	
		line = ft_strjoin(line, cmd[i]);
		if(cmd[++i])
			line = ft_strjoin(line, " ");
	}
	printf("%s",line);
	if(n == 1)
		printf("\n");
	return (1);
}

int	ft_echo(char **cmd,t_list	**data)
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
				if(echoprint(cmd, i, data))
					return (0);
			}
			else
				n++;
		}
		while(cmd[i][n] == 'n')
			n++;
		if(ft_strlen(cmd[i]) == n)
			i++;
		else
			if(echoprint(cmd, i, data))
				return (0);
	}
	echoprint(cmd, i, data);
	if(i == 1)
		printf("\n");
	return (0);
}	
