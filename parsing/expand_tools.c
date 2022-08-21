/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:44:01 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/20 19:54:12 by sfarhan          ###   ########.fr       */
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
		(*thief) = 2;
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
	char	*garbage;
	int		thief;

	end = NULL;
	garbage = NULL;
	thief = 0;
	end = after_world(more);
	dollar = assigning(more, end, env, &thief);
	if (dollar && thief != 1)
	{
		garbage = ft_strjoin(dollar, end);
		if (thief == 2)
			free (dollar);
		dollar = garbage;
	}
	else if (thief == 1)
		dollar = "";
	free (end);
	return (dollar);
}

static void	expand(char **assign, t_list **env, char *var)
{
	char	*dollar;
	char	**more;
	char	*garbage;
	int		y;

	y = 0;
	garbage = NULL;
	while (var[y])
	{
		if (var[y] == '$')
			break ;
		y++;
	}
	more = dq_undo(var);
	if (y > 0)
	{
		(*assign) = ft_strjoin(NULL, more[0]);
		y = 1;
	}
	while (more[y])
	{
		dollar = edges(more[y], env);
		if (dollar)
		{
			garbage = ft_strjoin((*assign), dollar);
			if (ft_strlen(*assign) != 0)
				free (*assign);
			(*assign) = garbage;
			if (ft_strlen(dollar) != 0)
				free (dollar);
		}
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
	if (ft_strlen(*var) == 0)
		g_exit_status = 7;
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
