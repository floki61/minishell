/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 02:53:39 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/30 08:24:27 by oel-berh         ###   ########.fr       */
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

int	home(t_list	**env)
{
	t_list	*tmp;
	char	*oldpwd;

	tmp = *env;
	oldpwd = getcwd(NULL, 0);
	if (chdir(findkey("HOME", &tmp)) == -1)
	{
		fperror("cd", ": HOME not set\n");
		return (1);
	}
	setpwd(*env);
	tmp = *env;
	if (!findkey("OLDPWD", &tmp) && !tmp)
		return (2);
	if (ft_strcmp(tmp->name, "OLDPWD"))
		return (2);
	if (!tmp->sep)
		tmp->sep = "=";
	free(tmp->value);
	tmp->value = oldpwd;
	return (2);
}

int	oldpwd(t_list **env)
{
	t_list	*tmp;
	char	*oldpwd;

	tmp = *env;
	oldpwd = ft_strdup(findkey("OLDPWD", &tmp));
	if (!oldpwd)
	{
		fperror("cd", ": OLDPWD not set\n");
		return (1);
	}
	if (!tmp->sep)
		tmp->sep = "=";
	free(tmp->value);
	tmp->value = getcwd(NULL, 0);
	chdir (oldpwd);
	printf ("%s\n", oldpwd);
	setpwd(*env);
	free (oldpwd);
	return (2);
}

int	newpwd(char *fd, t_list **env)
{
	t_list	*tmp;
	char	*oldpwd;

	tmp = *env;
	oldpwd = getcwd(NULL, 0);
	if (chdir(fd) < 0)
	{
		free (oldpwd);
		fperror(fd, ": No such file or directory\n");
		return (1);
	}
	setpwd(*env);
	if (!findkey("OLDPWD", &tmp) && !tmp)
	{
		free (oldpwd);
		return (2);
	}
	if (ft_strcmp(tmp->name, "OLDPWD"))
		return (2);
	if (!tmp->sep)
		tmp->sep = "=";
	free(tmp->value);
	tmp->value = oldpwd;
	return (2);
}

int	ft_cd(char **inpt, t_list **env)
{
	if (!inpt[1])
		return (home(env));
	if (foldername(inpt))
		return (2);
	if (!ft_strcmp(inpt[1], "-"))
		return (oldpwd(env));
	return (newpwd(inpt[1], env));
}
