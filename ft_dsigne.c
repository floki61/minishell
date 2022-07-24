/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsigne.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 23:44:48 by oel-berh          #+#    #+#             */
/*   Updated: 2022/07/24 01:10:06 by oel-berh         ###   ########.fr       */
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
	while(env[i])
		i++;
	printf("lentof$ %d\n",i);
	
	operation = malloc(sizeof(char *) * i);
	i = 0;
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

int exist_h(char *str,char c)
{
	int i;
	char **str2;

	i = 0;
	while(str[i])
	{
		if(str[i] == c)
		{
			str2 = ft_split(str,'=');
			if(str2[0][0] >= '0' && str2[0][0] <= '9')
			{
				printf("export:	'%s': not a valid identifier\n",str);
				return (0);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

char *ft_export(char *inpt,char **env)
{
	int i;
	char **cmd;

	i = 0;
	cmd = ft_split(inpt,' ');
	i++;
	while(cmd[i])
	{
		if(exist_h(cmd[i], '='))
		{
			if(*env)
				*env = ft_strjoin(*env,"\n");	
			*env = ft_strjoin(*env ,cmd[i]);
		}
		i++;
	}
	// printf("envnow = %s\n",*env);
	return(*env);
}


int	if_dsigne(char *inpt,char **envp)
{
	char **op;
	int i = 0;

	if(strcmp(inpt,"env") == 0 && envp)
	{
		while(envp[i])
		{
			printf("%s\n",envp[i]);
			i++;
		}
		exit(0);
	}
	if(ft_strncmp(inpt,"export ",7) == 0)
	{
		// printf("[export]\n");
		*envp = ft_export(inpt,envp);
		// printf("[env]: %s\n",*env);
		return (0);
	}
	
	if(*inpt == '$')
	{
		inpt++;
		op = forenv(envp);
		while(op[i])
		{
			if(strcmp(inpt,op[i]) == 0)
			{
				exdsigne(op[i],envp);
				return(0);
			}
			i++;
		}
	}
	return(1);
}