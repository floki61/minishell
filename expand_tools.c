/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:44:01 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/11 01:55:34 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*assigning(char *more, char *end, t_list **env, int *thief)
{
	int		i;
	t_list *tmp;
	char	*dollar;

	i = 0;
	tmp = *env;
	if(ft_strcmp(more, ft_strjoin("?", end)) == 0)
	{
		dollar = ft_itoa(exit_status);
		end = NULL;
		return (dollar);
	}
	while (tmp)
	{
		if (ft_strcmp(more, ft_strjoin(tmp->name, end)) == 0)
		{
			dollar = tmp->value;
			end = NULL;
			break ;
		}
		tmp = tmp->next;
		if (tmp == NULL)
		{
			(*thief) = 1;
			dollar = "";
		}
	}
	return (dollar);
}

static char	*edges(char *more, t_list **env)
{
	char	*end;
	char	*dollar;
	char	quote[3];
	int		thief;

	end = NULL;
	thief = 0;
	quote[0] = 34;
	quote[1] = 39;
	quote[2] = ' ';
	if (ft_skip(more, quote))
		end = after_world(more);
	dollar = assigning(more, end, env, &thief);
	if (ft_skip(more, quote))
	{
		if (dollar && thief != 1)
			dollar = ft_strjoin(dollar, after_world(more));
		else if (thief == 1)
			dollar = after_world(more);
	}
	return (dollar);
}

static char	*undo(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 2)
			str[i] = '$';
		i++;
	}
	return (str);
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
	more = ft_splito(var, '$');
	if (y > 0)
	{
		(*assign) = ft_strjoin((*assign), more[0]);
		y = 1;
	}
	while (more[y])
	{
		dollar = edges(more[y], env);
		if (dollar)
			(*assign) = ft_strjoin((*assign), dollar);
		dollar = NULL;
		y++;
	}
}

char	*if_dsigne(char *inpt, t_list **env, t_quote quote, int *x)
{
	char	*assign;
	char	sign[1];
	char	**var;
	int		j;

	j = 0;
	sign[0] = 2;
	assign = NULL;
	var = cashier(inpt);
	while (var[j])
	{
		if (quote.quote[(*x)] == 1)
			expand(&assign, env, var[j]);
		else
		{
			if (ft_skip(var[j], sign))
				var[j] = undo(var[j]);
			assign = ft_strjoin(assign, var[j]);
		}
		(*x)++;
		j++;
	}
	return (assign);
}
