/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:00:43 by oel-berh          #+#    #+#             */
/*   Updated: 2022/07/30 02:48:29 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_cd(char **inpt, char **path)
{
	char *oldpath;
	
	oldpath = NULL;
	if(inpt[2])
	{
		printf("cd: too many arguments\n");
		return (0);
	}
	if(!ft_strcmp(inpt[1],"-"))
	{
		oldpath = *path;
		*path = getcwd(NULL, 0);
		chdir(oldpath);
		printf("~%s\n",oldpath);
		free(oldpath);
		return (0);
	}
	*path = getcwd(NULL, 0);
	if(chdir(inpt[1]) < 0)
		printf("cd: no such file or directory: %s\n",inpt[1]);
	return (0);
}

void	*ft_pwd(char **inpt)
{
	char *cwd;

	if(inpt[1])
		printf("pwd: too many arguments\n");
	cwd = malloc(sizeof(char) * 100);
	getcwd(cwd, 100);
	printf("pwd=%s\n",cwd);
	return (0);
}


int		bult_1(char	**inpt, char **path)
{
	if(ft_strcmp(inpt[0],"cd") == 0)
	{
		ft_cd(inpt, path);
		return (1);
	}
	else if(ft_strcmp(inpt[0],"pwd") == 0 )
	{
		ft_pwd(inpt);
		return (1);
	}
	else if(ft_strcmp(inpt[0],"exit") == 0)
	{
		printf ("exit\n");
		exit(1);
	}
	return (0);
}

int		bult_2(char	**inpt,t_list	**data)
{
	
	if(ft_strcmp(inpt[0],"env") == 0)
	{
		printenvp(inpt,data);
		return(1);
	}
	else if(ft_strcmp(inpt[0],"export") == 0)
	{
		ft_export(inpt,data);
		return (1);
	}
	else if (ft_strcmp(inpt[0],"unset") == 0)
	{
		ft_unset(inpt,data);
		return (1);
	}
	else if(ft_strcmp(inpt[0], "echo") == 0)
	{
		ft_echo(inpt,data);
		return(1);
	}
	return (0);
}

int if_builtins(char **inpt, t_list **data, char **path)
{
	if(ft_strcmp(inpt[0],"exit") == 0)
	{
		printf ("exit\n");
		return (2);
	}
	if(bult_1(inpt, path) || bult_2(inpt,data))
		return (1);
	return (0);
}

// int ft_dollars(char *inpt, t_list **data)
// {
// 	t_list *tmp;

// 	tmp = NULL;
// 	inpt++;
// 	tmp = *data;
// 	while(tmp)
// 	{
// 		if(strcmp(tmp->name,inpt) == 0)
// 		{
// 			printf("%s\n",tmp->value);
// 			return(0);
// 			}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }