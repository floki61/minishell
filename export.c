/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:00:44 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/04 18:30:50 by oel-berh         ###   ########.fr       */
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

int     v_position(char *str, char c)
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

int     n_position(char *str, char c)
{
    int i;

    i = 0;
    if(str[0] == c)
        return(1);
	else if(str[0] >= '0' && str[0] <= '9')
		return (3);
    while(str[i])
    {
		if((str[i] >= 34 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 64)) //$ # () -
		{
			if(str[i] == '+' && !str[i + 1])
				return (0);
			return (3);
		}
		else if((str[i] >= 91 && str[i] <= 96) || (str[i] >= 123 && str[i] <= 126))
		{
			if(str[i] != 95)
				return (3);
		}
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
            pos = n_position(str2[0], '!');
			
            if(pos == 1)
            {
                while(*str != '!')
                   str++;
                printf("minishell: %s: event not found\n",str);
                return (0);
            }
			else if(pos == 3)
			{
				printf("minishell: export: '%s': not a valid identifier\n",str);
				return (0);
			}
			while(*str != '=')
				str++;
			pos = v_position(str, '!');
			if(pos == 1)
			{
				 while(*str != '!')
                   str++;
				 printf("minishell: %s: event not found\n",str);
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

void	*ft_export(char **cmd, t_list **data)
{
	t_list *tmp;
	char	**op;
	char    *value;
	char 	*str;
	int		i;
	int		j;
	
	i = 1;
	j = 0;
	str = NULL;
	if(!cmd[i] || cmd[i][0] == '#')
	{
		ft_printenv(*data);
		return (0);
	}
	while(cmd[i])
	{
		j = 0;
		tmp = *data;
		if(!exist_h(cmd[i], '='))
			return (0);
		while(cmd[i][0] == '#')
			i++;
		op = ft_split(cmd[i], '=', 0);
		if(op[0][ft_strlen(op[0]) - 1] == '+')
		{
			op[0][ft_strlen(op[0]) - 1] = '\0';
			j++;
		}
		while(tmp)
		{
			if(ft_strcmp(op[0],tmp->name) == 0)
			{
				value = cmd[i];
    	        while(*value != '=')
    	            value++;
				if(j == 1)
					tmp->value = ft_strjoin(tmp->value,++value);
				else
				{
					tmp->value = ++value;
					printf("value1: %s\n",tmp->value);
				}
				j = 3;
				break ;
			}
			tmp = tmp->next;
		}
		if(j != 3)
		{
			j = 0;
			value = cmd[i];
    		while(*value != '=')
    	    	value++;
			ft_lstadd_back(data,ft_lstnew(op[0],++value));
		}
		i++;
	}
	return (0);
}

