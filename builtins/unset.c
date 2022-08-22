/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:10:50 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/22 01:39:20 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	firstnode(t_list **head)
{
	t_list	*temp;

	temp = *head;
	free((*head)->name);
	free((*head)->value);
	*head = (*head)->next;
	free(temp);
}

void	deletenode(t_list **head, char *name)
{
	t_list	*temp;
	t_list	*current;

	if (ft_strcmp((*head)->name, name) == 0)
		firstnode(head);
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			if (ft_strcmp(current->next->name, name) == 0)
			{
				temp = current->next;
				free(current->next->name);
				free(current->next->value);
				current->next = current->next->next;
				free(temp);
				break ;
			}
			else
				current = current->next;
		}
	}
}

int	ft_unset(char **cmd, t_list **data)
{
	int		i;

	i = 1;
	while (cmd[i])
	{
		deletenode(data, cmd[i]);
		i++;
	}	
	return (2);
}
