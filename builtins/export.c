/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:00:44 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/21 17:23:56 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	withoutvalue(char *cmd, t_list	**data)
{
	t_list	*tmp;

	tmp = *data;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, cmd) == 0)
			return (0);
		tmp = tmp->next;
	}
	ft_lstadd_back(data, ft_lstnew(ft_strdup(cmd), NULL, NULL));
	return (0);
}

int	withvalue(char *cmd, t_list **data)
{
	char	**op;
	char	*value;
	char	c;
	t_list	*tmp;

	tmp = *data;
	op = ft_split(cmd, '=', 0);
	c = '-';
	if (op[0][ft_strlen(op[0]) - 1] == '+')
	{
		op[0][ft_strlen(op[0]) - 1] = '\0';
		c = '+';
	}
	if (existkey(cmd, op, data, c))
		return (2);
	value = skip_c(cmd, '=');
	ft_lstadd_back(data, ft_lstnew(ft_strdup(op[0]), ft_strdup(++value), "="));
	free_tab(op, 0);
	return (2);
}

int	export(char **cmd, t_list **data)
{
	int	i;
	int	sep;

	i = 1;
	while (cmd[i])
	{
		sep = check_exp(cmd[i]);
		if ((cmd[i][ft_strlen(cmd[i]) - 1] == '=' && sep == -1) || !sep)
			withvalue(cmd[i], data);
		else if (sep == -1)
			sep = withoutvalue(cmd[i], data);
		else
			return (sep);
		i++;
	}
	return (2);
}

int	ft_export(char **cmd, t_list **data)
{
	if (!cmd[1] || cmd[1][0] == '#')
	{
		print_exp(*data);
		return (2);
	}
	return (export(cmd, data));
}
