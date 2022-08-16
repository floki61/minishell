/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 01:19:30 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/16 02:26:49 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*findkey(char *key, t_list **env)
{
	while (*env)
	{
		if (!ft_strcmp((*env)->name, key))
			return ((*env)->value);
		(*env) = (*env)->next;
	}
	return (NULL);
}

int		home(t_list **env,t_list *tmp)
{
	findkey("OLDPWD", &tmp);
	tmp->value = getcwd(NULL, 0);
	tmp = *env;
	chdir(findkey("HOME", &tmp));
	return (2);
}

int		oldpwd(char *oldpath, t_list *tmp)
{
	oldpath = findkey("OLDPWD", &tmp);
	tmp->value = getcwd(NULL, 0);
	chdir(oldpath);
	printf("~%s\n", oldpath);
	return (2);
}

int		newpwd(char *fd, t_list *tmp)
{
	findkey("OLDPWD", &tmp);
	tmp->value = getcwd(NULL, 0);
	if (chdir(fd) < 0)
	{
		printf("cd: no such file or directory: %s\n", fd);
		return (1);
	}
	return (2);
}

int	ft_cd(char **inpt, t_list **env)
{
	t_list	*tmp;
	char	*oldpath;

	oldpath = NULL;
	tmp = *env;
	if (!inpt[1])
		return(home(env,tmp));
	if (!ft_strcmp(inpt[1], "-"))
		return(oldpwd(oldpath ,tmp));
	return(newpwd(inpt[1], tmp));
}

int	ft_pwd(char **inpt)
{
	char	*cwd;
	int		i;
	int		n;

	cwd = NULL;
	i = 1;
	n = 0;
	while (inpt[i])
	{
		if (v_position(inpt[i], '!') == 1)
		{
			while (*inpt[i] != '!')
				inpt[i]++;
			printf("minishell: %s: event not found\n", inpt[i]);
			return (2);
		}
		i++;
	}
	cwd = getcwd(NULL, 0);
	printf("pwd=%s\n", cwd);
	return (2);
}

int	bult_1(char	**inpt)
{
	if (ft_strcmp(inpt[0], "echo") == 0)
		return (ft_echo(inpt));
	else if (ft_strcmp(inpt[0], "pwd") == 0)
		return (ft_pwd(inpt));
	return (0);
}

int	bult_2(char	**inpt, t_list **data)
{
	if (ft_strcmp(inpt[0], "env") == 0)
		return (printenvp(inpt, data));
	else if (ft_strcmp(inpt[0], "export") == 0)
		return (ft_export(inpt, data));
	else if (ft_strcmp(inpt[0], "unset") == 0)
		return (ft_unset(inpt, data));
	else if (ft_strcmp(inpt[0], "cd") == 0)
		return (ft_cd(inpt, data));
	return (0);
}

int	if_builtins(char **inpt, t_list **data)
{
	int	status;

	status = bult_1(inpt);
	if (status)
		return (status);
	else
	{
		status = bult_2(inpt, data);
		if (status)
			return (status);
	}
	return (0);
}
