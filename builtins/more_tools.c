/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 02:22:19 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/21 04:48:41 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*skip_c(char *str, char c)
{
	while (*str && *str != c)
		str++;
	return (str);
}

// still 1 leaks

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
				join = ft_strjoin(tmp->value, join);
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

void	fperror(char *arg, char *error)
{
	write(2, "minishell: ", 11);
	write(2, arg, ft_strlen(arg));
	write(2, error, ft_strlen(error));
}
