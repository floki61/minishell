/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 02:22:19 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/30 08:24:43 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*skip_c(char *str, char c)
{
	while (*str && *str != c)
		str++;
	return (str);
}

char	*joinvalue(char	*key, t_list *tmp)
{
	char	*join2;

	join2 = ft_strdup(key);
	free (key);
	key = ft_strjoin(tmp->value, join2);
	free(join2);
	return (key);
}

int	existkey(char *cmd, char **op, t_list **data, char c)
{
	t_list	*tmp;
	char	*join;

	tmp = *data;
	join = NULL;
	while (tmp)
	{
		if (!ft_strcmp(op[0], tmp->name))
		{
			cmd = skip_c(cmd, '=');
			if (!tmp->sep)
				tmp->sep = "=";
			join = ft_strdup(++cmd);
			if (c == '+')
				join = joinvalue(join, tmp);
			free(tmp->value);
			tmp->value = ft_strdup(join);
			free(join);
			free_tab(op, 0);
			return (2);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	foldername(char **inpt)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (inpt[i])
	{
		if (v_position(inpt[i], '!') == 2)
		{
			while (inpt[i][n] != '!')
				n++;
			fperror(&inpt[i][n], ":event not found\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	setpwd(t_list *env)
{
	if (!findkey("PWD", &env) && !env)
		return ;
	if (ft_strcmp(env->name, "PWD"))
		return ;
	if (!env->sep)
		env->sep = "=";
	free(env->value);
	env->value = getcwd(NULL, 0);
}
