/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:00:44 by oel-berh          #+#    #+#             */
/*   Updated: 2022/07/29 22:21:01 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int     c_position(char *str, char c)
{
    int i;

    i = 0;
    if(str[0] == c)
        return(1);
    while(str[i])
    {
        if(str[i] == c)
        {
            if(!str[i + 1])
                return(3);
            return(1);
        }
        i++;
    }
    return (0);
}

int exist_h(char *str,char c)
{
	int i;
    int pos;
	char **str2;

	i = 0;
	while(str[i])
	{
		if(str[i] == c)
		{
            
			str2 = ft_split(str,'=', 0);
            pos = c_position(str2[0], '!');
            if(pos == 1)
            {
                while(*str != '!')
                   str++;
                printf("%s: event not found\n",str);
                return (0);
            }
			if((str2[0][0] >= '0' && str2[0][0] <= '9') || pos == 3)
			{
				printf("export:	'%s': not a valid identifier\n",str);
				return (0);
			}
			while(*str != '=')
				str++;
			pos = c_position(str, '!');
			if(pos == 1)
			{
				 while(*str != '!')
                   str++;
				 printf("%s: event not found\n",str);
				 return (0);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_printenv(t_list *data)
{
	t_list *tmp;
	t_list *tmp2;
	char *name;
	char *value;
	// int pos;

	tmp = data;
	while(tmp)
	{
		tmp2 = tmp->next;
		while(tmp2)
		{
			if(ft_strcmp(tmp->name,tmp2->name) > 0)
			{
				name = tmp->name;
				value = tmp->value;
				tmp->name = tmp2->name;
				tmp->value = tmp2->value;
				tmp2->name = name;
				tmp2->value = value;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	tmp = data;
	while(tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->name,tmp->value);
		tmp = tmp->next;
	}
}

void 	*ft_export(char **cmd,t_list **data)
{
	int		i;
	t_list	*tmp;
	char	**op;
    char    *value;
	
	i = 1;
	tmp = *data;
	if(!cmd[1])
		ft_printenv(*data);
	while(cmd[i])
	{
		if(exist_h(cmd[i], '='))
		{
			op = ft_split(cmd[i], '=', 0);
			while(tmp)
			{
				if(ft_strcmp(op[0],tmp->name) == 0)
				{
                    value = cmd[i];
                    while(*value != '=')
                         value++;
					tmp->value = ++value;
					break ;
				}
				tmp = tmp->next;	
			}
            value = cmd[i];
            while(*value != '=')
                value++;
			ft_lstadd_back(data,ft_lstnew(op[0],++value));
		}	
		i++;
	}
	return(0);
}