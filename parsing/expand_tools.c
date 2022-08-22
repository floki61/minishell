/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:44:01 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/21 22:53:27 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	compound(char **more, char **assign, t_list **env, int y)
{
	char	*garbage;
	char	*dollar;

	garbage = NULL;
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

static void	expand(char **assign, t_list **env, char *var)
{
	char	**more;
	int		y;
	char	*garbage;

	garbage = NULL;
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
		garbage = ft_strjoin((*assign), more[0]);
		if (ft_strlen(*assign) != 0)
			free (*assign);
		(*assign) = garbage;
		y = 1;
	}
	compound(more, assign, env, y);
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
		g_global.exit = 7;
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
