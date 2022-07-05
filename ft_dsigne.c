/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsigne.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 23:44:48 by oel-berh          #+#    #+#             */
/*   Updated: 2022/07/05 23:44:49 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **forenv(char **env)
{
	int     i;
	int     j;
    char     **op;
	char     **operation;
	
	i = 0;
	j = 0;
	operation = malloc(sizeof(char *) * 31);
	while(env[i])
	{
        op = ft_split(env[i], '=');
		operation[i] = op[0];
		i++;
	}
	operation[i] = 0;
	return(operation);
}
int	exdsigne(char *op,char **env)
{
	char **operation;
	int i;

	i = 0;
	while(env[i])
	{
		if(ft_strncmp(op,env[i],ft_strlen(op)) == 0)
		{
			operation = ft_split(env[i],'=');
			printf("%s\n",operation[1]);
			return (0);
		}
		i++;
	}
	return(1);
}

int	if_dsigne(char *inpt,char **env)
{
	char **op;
	int i = 0;

	if(*inpt == '$')
	{
		inpt++;
		op = forenv(env);
		while(op[i])
		{
			if(strcmp(inpt,op[i]) == 0)
			{
				exdsigne(op[i],env);
				return(0);
			}
			i++;
		}
	}
	return(1);
}