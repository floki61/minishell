/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsigne.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 23:44:48 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/01 00:31:04 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_merge(char *str, char *buf)
{
	int		i;
	int		j;
	int		x;
	int		count;
	char	*merge;

	i = 0;
	j = 0;
	count = 0;
	while (buf[i])
	{
		if (buf[i] == 1)
			i++;
		else if (buf[i] == '$')
		{
			while (buf[i] != 1)
				i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	merge = malloc (sizeof(char) * ft_strlen(str) + count + 1);
	i = 0;
	while (buf[i])
	{
		if (buf[i] == 1)
			i++;
		else if (buf[i] == '$')
			break ;
		else
		{
			merge[j] = buf[i];
			j++;
			i++;
		}
	}
	x = 0;
	while (str[x])
	{
		merge[j] = str[x];
		j++;
		x++;
	}
	while (buf[i] != 1)
		i++;
	while (buf[i])
	{
		if (buf[i] == 1)
			i++;
		else
		{
			merge[j] = buf[i];
			j++;
			i++;
		}
	}
	merge[j] = '\0';
	return (merge);
}

char	*if_dsigne(char *inpt, t_list **env)
{
	t_list	*envp;
	char	*dollar;
	char	tmp[3];
	char	**var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp[0] = 34;
	tmp[1] = 39;
	tmp[2] = 1;
	envp = *env;
	//put unprintable char then undo
	var = ft_advanced(inpt, tmp);
	while (var[j])
	{
		if (var[j][0] == '$')
			break ;
		j++;
	}
	if (var[j] == NULL)
		return (0);
	i = 0;
	if (var[j][0] == '$')
	{
		var[j]++;
		if(var[j][1] == '?')
		{
			
		}
		while (envp)
		{
			if (strcmp(var[j], envp->name) == 0)
			{
				dollar = ft_merge(envp->value, inpt);
				return (dollar);
			}
			envp = envp->next;
		}
	}
	return (0);
}
