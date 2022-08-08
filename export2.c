/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:47:46 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/07 20:34:41 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    withoutsep(char *cmd, t_list    **data)
{
    t_list *tmp;

    tmp = *data;
    if(check_exp(cmd))
	{
        while(tmp)
        {
            if(ft_strcmp(tmp->name,cmd) == 0)
                return ;
            rmp = tmp->next;
        }
		ft_lstadd_back(data,ft_lstnew(cmd, NULL, NULL));
		return ;
	}
	else
		exit(0);
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
		while (!exist_sep(cmd[i]))
        {
            withoutsep(cmd[i],data);
            i++;
        }
        if(!check_exp(cmd[i]))
            exit(0);
		if(cmd[i][0] == '#')
			exit(0);
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
				if(!tmp->sep)
					continue;
				else if(j == 1)
					tmp->value = ft_strjoin(tmp->value,++value);
				else
					tmp->value = ++value;
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
			ft_lstadd_back(data,ft_lstnew(op[0],++value, "="));
		}
		i++;
	}
	return (0);
}