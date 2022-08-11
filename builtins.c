/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:00:43 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/11 03:52:46 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **inpt, char **path)
{
	char *oldpath;
	
	oldpath = NULL;
	// if(inpt[2])
	// {
	// 	printf("cd: too many arguments\n");
	// 	return (2);
	// }
	if(!ft_strcmp(inpt[1],"-"))
	{
		printf("path-\n");
		oldpath = *path;
		*path = getcwd(NULL, 0);
		chdir(oldpath);
		printf("~%s\n",oldpath);
		free(oldpath);
		return (2);
	}
	*path = getcwd(NULL, 0);
	if(chdir(inpt[1]) < 0)
	{
		printf("cd: no such file or directory: %s\n",inpt[1]);
		return (1);
	}
	return (2);
}

int	ft_pwd(char **inpt)
{
	char *cwd;

	cwd = NULL;
	if(inpt[1])
		printf("pwd: too many arguments\n");
	cwd = getcwd(NULL, 0);
	printf("pwd=%s\n",cwd);
	return (2);
}


int		bult_1(char	**inpt, t_list **data)
{
	if(ft_strcmp(inpt[0], "echo") == 0)
		return(ft_echo(inpt,data));
	else if(ft_strcmp(inpt[0],"pwd") == 0 )
		return(ft_pwd(inpt));
	else if(ft_strcmp(inpt[0],"exit") == 0)
	{
		printf ("waaaexit\n");
		exit(1);
	}
	return (0);
}

int		bult_2(char	**inpt,t_list	**data, char **path)
{
	
	if(ft_strcmp(inpt[0],"env") == 0)
		return (printenvp(inpt,data));
	else if(ft_strcmp(inpt[0],"export") == 0)
		return (ft_export(inpt,data));
	else if (ft_strcmp(inpt[0],"unset") == 0)
		return (ft_unset(inpt,data));
	else if(ft_strcmp(inpt[0],"cd") == 0)
		return (ft_cd(inpt, path));
	return (0);
}

int if_builtins(char **inpt, t_list **data, char **path)
{
	int status;
	
	status = bult_1(inpt, data);
	if(status)
		return (status);
	else
	{
		status = bult_2(inpt, data, path);
		if(status)
		 	return (status);
	}
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
