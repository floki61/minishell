/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 03:07:13 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/16 03:26:57 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_exp(t_list **data)
{
	t_list	*tmp;
	t_list	*tmp2;
	char	*name;
	char	*value;

	tmp = *data;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->name, tmp2->name) > 0 && tmp2->value != NULL
				&& tmp->value != NULL)
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
}

void	print_exp(t_list *data)
{
	t_list	*tmp;

	sort_exp(&data);
	tmp = data;
	while (tmp)
	{
		if (tmp->sep)
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		else
			printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
}
