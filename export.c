/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:00:44 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/11 05:11:18 by oel-berh         ###   ########.fr       */
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
int exist_sep(char *str)
{
	int i;
	
	i = 0;
	while(str[i])
	{
		if(str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_exp(char *str)
{
	int i;
    int pos;
	char **str2;

	i = 0;
	str2 = ft_split(str,'=', 0);
    pos = n_position(str2[0], '!');
			
	write(1, "check_exp\n",10);
    if(pos == 1)
    {
        while(*str != '!')
            str++;
        printf("minishell: %s: event not found\n",str);
        return (2);
     }
	else if(pos == 3)
	{
		printf("minishell: export: '%s': not a valid identifier\n",str);
		return (1);
	}
	if(!str2[1])
		return(0);
	while(*str != '=')
		str++;
	pos = v_position(str, '!');
	if(pos == 1)
	{
		 while(*str != '!')
             str++;
		 printf("minishell: %s: event not found\n",str);
			return (2);
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
			if(ft_strcmp(tmp->name,tmp2->name) > 0 && tmp2->value != NULL && tmp->value != NULL)
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
		if(tmp->sep)
			printf("declare -x %s=\"%s\"\n", tmp->name,tmp->value);
		else
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
}

int    withoutsep(char *cmd, t_list    **data)
{
	int error;
    t_list *tmp;

    tmp = *data;
	error = check_exp(cmd);
	printf("error: %d\n",error);
    if(!error)
	{
        while(tmp)
        {
            if(ft_strcmp(tmp->name,cmd) == 0)
                return (0);
            tmp = tmp->next;
        }
		printf("whitoutsep\n");
		ft_lstadd_back(data,ft_lstnew(cmd, NULL, NULL));
		return (0);
	}
	else
		return(error);
}

int	ft_export(char **cmd, t_list **data)
{
	t_list *tmp;
	char	**op;
	char    *value;
	char 	*str;
	int		i;
	int		j;
	int		sep;
	
	i = 1;
	j = 0;
	str = NULL;
	if(!cmd[i] || cmd[i][0] == '#')
	{
		ft_printenv(*data);
		return (2);
	}
	while(cmd[i])
	{
		j = 0;
		tmp = *data;
		while (!exist_sep(cmd[i]))
        {
			sep = withoutsep(cmd[i],data);
			printf("sep: %d\n",sep);
            if(sep)
				return(sep);
			if(!cmd[++i])
				return (2);
        }
		sep = check_exp(cmd[i]);
        if(sep)
            return (sep);
		if(cmd[i][0] == '#')
			return (2);
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
					tmp->sep = "=";
				if(j == 1)
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
			// printf("n: %s v: %s\n",op[0],++value);
			ft_lstadd_back(data,ft_lstnew(op[0],++value, "="));
		}
		i++;
	}
	return (2);
}

// void	*ft_export(char **cmd, t_list **data)
// {
// 	t_list *tmp;
// 	char	**op;
// 	char    *value;
// 	char 	*str;
// 	int		i;
// 	int		j;
	
// 	i = 1;
// 	j = 0;
// 	str = NULL;
// 	if(!cmd[i] || cmd[i][0] == '#')
// 	{
// 		ft_printenv(*data);
// 		return (0);
// 	}
// 	while(cmd[i])
// 	{
// 		j = 0;
// 		tmp = *data;
// 		if(!exist_sep(cmd[i]))
// 		{
// 			if(check_exp(cmd[i]))
// 			{
// 				ft_lstadd_back(data,ft_lstnew(cmd[i], NULL, NULL));
// 				return (0);
// 			}
// 			else
// 				return (0);
// 		}
// 		while(cmd[i][0] == '#')
// 			i++;
// 		op = ft_split(cmd[i], '=', 0);
// 		if(op[0][ft_strlen(op[0]) - 1] == '+')
// 		{
// 			op[0][ft_strlen(op[0]) - 1] = '\0';
// 			j++;
// 		}
// 		while(tmp)
// 		{
// 			if(ft_strcmp(op[0],tmp->name) == 0)
// 			{
// 				value = cmd[i];
//     	        while(*value != '=')
//     	            value++;
// 				if(!tmp->sep)
// 					continue;
// 				else if(j == 1)
// 					tmp->value = ft_strjoin(tmp->value,++value);
// 				else
// 					tmp->value = ++value;
// 				j = 3;
// 				break ;
// 			}
// 			tmp = tmp->next;
// 		}
// 		if(j != 3)
// 		{
// 			j = 0;
// 			value = cmd[i];
//     		while(*value != '=')
//     	    	value++;
// 			ft_lstadd_back(data,ft_lstnew(op[0],++value, "="));
// 		}
// 		i++;
// 	}
// 	return (0);
// }

