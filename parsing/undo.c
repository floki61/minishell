/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 19:27:13 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/18 21:01:18 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**dq_undo(char *var)
{
	char	**more;
	int		i;

	i = 0;
	more = ft_splito(var, '$');
	while (more[i])
	{
		more[i] = undo(more[i], 3);
		i++;
	}
	return (more);
}

char	*sq_undo(char *var)
{
	char	sign[2];

	sign[0] = 2;
	sign[1] = 3;
	if (ft_skip(var, sign))
	{
		var = undo(var, 3);
		var = undo(var, 2);
	}
	return (var);
}

char	*undo(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			str[i] = '$';
		i++;
	}
	return (str);
}
