/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 01:19:30 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/07 19:57:55 by sfarhan          ###   ########.fr       */
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
			str2 = ft_split(str,'=', 0);
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
		op = ft_split(envp[i], '=', 0);
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

void 	*ft_unset(char **cmd,t_list **data)
{
	int i;
	t_list *tmp;

	i = 1;
	tmp = *data;
	while(cmd[i])
	{
		deletenode(data,cmd[i]);
		i++;
	}	
	return(0);
}

void	ft_printenv(t_list *data)
{
	t_list *tmp;
	t_list *tmp2;
	char *name;
	char *value;

	tmp = data;
	while(tmp)
	{
		tmp2 = tmp->next;
		while(tmp2)
		{
			if(strcmp(tmp->name,tmp2->name) > 0)
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
		printf("declare -x ");
		printf("%s->%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

void 	*ft_export(char **cmd,t_list **data)
{
	int		i;
	t_list	*tmp;
	char	**op;
	
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
		printf("%s>>>%s\n",tmp->name,tmp->value);
		tmp = tmp->next;
	}
	return(0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] == s2[j] && s1[i] != '\0' && s2[j] != '\0')
	{
		i++;
		j++;
	}
	if (s2[j] == '\n')
		j++;
	return (s1[i] - s2[j]);
}

int if_builtins(char **inpt,char **envp, t_list **data)
{
	if(ft_strcmp(inpt[0],"cd") == 0)
	{
		if(inpt[2])
			printf("cd: too many arguments\n");
		if(chdir(inpt[1]) < 0)
			printf("cd: no such file or directory: %s\n",inpt[1]);
		return (0);
	}
	else if(ft_strcmp(inpt[0],"pwd") == 0 )
	{
		char *cwd;

		if(inpt[1])
			printf("pwd: too many arguments\n");
		cwd = malloc(sizeof(char) * 100);
		getcwd(cwd, 100);
		printf("pwd=%s\n",cwd);
		return (0);
	}
	else if(ft_strcmp(inpt[0],"exit") == 0)
	{
		printf ("exit\n");
		exit(0);
	}
	if(!(*data))
		ft_envp(envp,data);
	if(ft_strcmp(inpt[0],"env") == 0)
	{
		if(inpt[1])
			printf("env: %s: NO such file or directory\n",inpt[1]);
		printenvp(data);
		return(0);
	}
	else if(ft_strcmp(inpt[0],"export") == 0)
	{
		ft_export(inpt,data);
		return (0);
	}
	else if (ft_strcmp(inpt[0],"unset") == 0)
	{
		ft_unset(inpt,data);
		return (0);
	}
	else if (ft_strcmp(inpt[0], "echo") == 0)
	{
		ft_echo(inpt, *data);
		exit (1);
	}
	return(1);
}
