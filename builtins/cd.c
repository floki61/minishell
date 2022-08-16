/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 02:53:39 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/16 03:17:48 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	home(t_list **env, t_list *tmp)
{
	findkey("OLDPWD", &tmp);
	tmp->value = getcwd(NULL, 0);
	tmp = *env;
	chdir(findkey("HOME", &tmp));
	return (2);
}

int	oldpwd(char *oldpath, t_list *tmp)
{
	oldpath = findkey("OLDPWD", &tmp);
	tmp->value = getcwd(NULL, 0);
	chdir(oldpath);
	printf("~%s\n", oldpath);
	return (2);
}

int	newpwd(char *fd, t_list *tmp)
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
		return (home(env, tmp));
	if (!ft_strcmp(inpt[1], "-"))
		return (oldpwd(oldpath, tmp));
	return (newpwd(inpt[1], tmp));
}
