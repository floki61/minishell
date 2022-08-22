/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 02:53:39 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/22 22:33:24 by oel-berh         ###   ########.fr       */
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
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	tmp = *env;
	if (chdir(findkey("HOME", &tmp)) == -1)
	{
		fperror("cd", ": HOME not set\n");
		return (1);
	}
	if (!findkey("OLDPWD", &tmp))
		return (2);
	free(tmp->value);
	tmp->value = oldpwd;
	return (2);
}

int	oldpwd(char *oldpath, t_list *tmp)
{
	oldpath = ft_strdup(findkey("OLDPWD", &tmp));
	if (!oldpath)
	{
		fperror("cd", ": OLDPWD not set\n");
		return (1);
	}
	free(tmp->value);
	tmp->value = getcwd(NULL, 0);
	chdir (oldpath);
	printf ("%s\n", oldpath);
	return (2);
}

int	newpwd(char *fd, t_list *tmp)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(fd) < 0)
	{
		write(2, "minishell: ", 11);
		write(2, "cd: ", 4);
		write(2, fd, ft_strlen(fd));
		write(2, " No such file or directory\n", 27);
		return (1);
	}
	if (!findkey("OLDPWD", &tmp))
		return (2);
	free(tmp->value);
	tmp->value = oldpwd;
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
	if (foldername(inpt))
		return (2);
	if (!ft_strcmp(inpt[1], "-"))
		return (oldpwd(oldpath, tmp));
	return (newpwd(inpt[1], tmp));
}
