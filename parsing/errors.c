/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:01:44 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/18 21:01:18 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_scanner(char *str)
{
	if (str[0] == '|' || ft_strcmp(str, ".") == 0 || ft_strcmp(str, "..") == 0
		|| ft_strcmp(str, "<<") == 0 || ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp (str, ">") == 0)
	{
		printf ("minishell: syntax error near unexpected token\n");
		return (0);
	}
	return (1);
}
