/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsigne.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 23:44:48 by oel-berh          #+#    #+#             */
/*   Updated: 2022/07/24 13:36:55 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	new->next = NULL;
	if (!(*alst))
		*alst = new;
	else
		(ft_lstlast(*alst))->next = new;
}


t_list	*ft_lstnew(void *name,void *value)
{
	t_list	*new;

	new = (t_list *) malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

void deletenode(t_list **head, char *name)
{
    t_list *temp;
	t_list *current;

    if(strcmp((*head)->name,name)== 0)
    {
        temp = *head;  
        *head = (*head)->next;
        free(temp);
    }
    else
    {
		current  = *head;
        while(current->next != NULL)
        {
            if(strcmp(current->next->name, name) == 0)
            {
                temp = current->next;
                current->next = current->next->next;
                free(temp);
                break;
            }
            else
            	current = current->next;
        }
    }
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

void	ft_envp(char **envp,t_list	**data)
{
	int i;
	char **op;
	
	i = 0;
	while(envp[i])
	{
		op = ft_split(envp[i], '=');
		ft_lstadd_back(data,ft_lstnew(op[0],op[1]));
		i++;
	}
	return ;
}

int ft_dollars(char *inpt, t_list **data)
{
	t_list *tmp;

	tmp = NULL;
	inpt++;
	tmp = *data;
	while(tmp)
	{
		if(strcmp(tmp->name,inpt) == 0)
		{
			printf("%s\n",tmp->value);
			return(0);
			}
		tmp = tmp->next;
	}
	return (0);
}

void 	*ft_unset(char *inpt,t_list **data)
{
	char 	**cmd;
	int i;
	t_list *tmp;

	cmd = ft_split(inpt,' ');
	i = 1;
	tmp = *data;
	while(cmd[i])
	{
		deletenode(data,cmd[i]);
		i++;
	}	
	return(0);
}

void 	*ft_export(char *inpt,t_list **data)
{
	int		i;
	t_list	*tmp;
	char	**op;
	char 	**cmd;
	
	i = 1;
	cmd = ft_split(inpt,' ');
	tmp = *data;
	while(cmd[i])
	{
		if(exist_h(cmd[i], '='))
		{
			op = ft_split(cmd[i], '=');
			while(tmp)
			{
				if(strcmp(op[0],tmp->name) == 0)
				{
					tmp->value = op[1];
					return(0);
				}
				tmp = tmp->next;	
			}
			ft_lstadd_back(data,ft_lstnew(op[0],op[1]));
		}	
		i++;
	}
	return(0);
}


int printenvp(t_list **data)
{
	t_list *tmp;

	tmp = NULL;
	tmp = *data;
	while (tmp)
	{
		printf("%s=%s\n",tmp->name,tmp->value);
		tmp = tmp->next;
	}
	return(0);
}

int	if_dsigne(char *inpt,char **envp,t_list **data)
{
	t_list *tmp;

	tmp = NULL;
	
	if(!(*data))
		ft_envp(envp,data);
	if(strcmp(inpt,"env") == 0)
	{
		printenvp(data);
		return(0);
	}
	if(ft_strncmp(inpt,"export ",7) == 0)
	{
		ft_export(inpt,data);
		return (0);
	}
	else if (ft_strncmp(inpt,"unset ",6) == 0)
	{
		ft_unset(inpt,data);
		return (0);
	}
	if(*inpt == '$')
	{
		ft_dollars(inpt,data);
		return (0);
	}
	return(1);
}