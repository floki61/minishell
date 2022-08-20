/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:44:01 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/18 23:22:34 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*assigning(char *more, char *end, t_list **env, int *thief)
{
	int		i;
	t_list	*tmp;
	char	*dollar;
	char	*garbage;

	i = 0;
	tmp = *env;
	dollar = NULL;
	garbage = ft_strjoin("?", end);
	if (ft_strcmp(more, garbage) == 0)
	{
		dollar = ft_itoa(g_exit_status);
		free (garbage);
		return (dollar);
	}
	free (garbage);
	while (tmp)
	{
		garbage = ft_strjoin(tmp->name, end);
		if (ft_strcmp(more, garbage) == 0)
		{
			dollar = tmp->value;
			end = NULL;
			free (garbage);
			break ;
		}
		tmp = tmp->next;
		if (tmp == NULL)
			(*thief) = 1;
		free (garbage);
	}
	return (dollar);
}

static char	*edges(char *more, t_list **env)
{
	char	*end;
	char	*dollar;
	int		thief;

	end = NULL;
	thief = 0;
	end = after_world(more);
	dollar = assigning(more, end, env, &thief);
	if (dollar && thief != 1)
		dollar = ft_strjoin(dollar, end);
	else if (thief == 1)
		dollar = "";
	free (end);
	return (dollar);
}

static void	expand(char **assign, t_list **env, char *var)
{
	char	*dollar;
	char	**more;
	int		y;

	y = 0;
	while (var[y])
	{
		if (var[y] == '$')
			break ;
		y++;
	}
	more = dq_undo(var);
	if (y > 0)
	{
		(*assign) = ft_strjoin((*assign), more[0]);
		y = 1;
	}
	while (more[y])
	{
		dollar = edges(more[y], env);
		printf ("p => %p\n", (*assign));
		if (dollar)
			(*assign) = ft_strjoin((*assign), dollar);
		free (dollar);
		y++;
	}
	free_tab(more, 0);
}

char	*if_dsigne(char *inpt, t_list **env, t_quote *quote)
{
	char	*assign;
	char	**var;
	int		j;

	j = 0;
	assign = "";
	var = cashier(inpt);
	while (var[j])
	{
		if (quote->quote[(quote->x)] != 2)
			expand(&assign, env, var[j]);
		else
		{
			var[j] = sq_undo(var[j]);
			assign = ft_strjoin(assign, var[j]);
		}
		(quote->x)++;
		j++;
	}
	free_tab (var, 0);
	return (assign);
}
