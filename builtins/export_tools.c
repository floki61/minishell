/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 03:08:59 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/16 03:26:28 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	spchar(char *str, int i)
{
	if ((str[i] >= 34 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 64))
	{
		if (str[i] == '+' && !str[i + 1] && i != 0)
			return (0);
		return (1);
	}
	else if ((str[i] >= 91 && str[i] <= 96)
		|| (str[i] >= 123 && str[i] <= 126))
	{
		if (str[i] != 95)
			return (1);
	}
	return (3);
}

int	v_position(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (!str[i + 1])
				return (0);
			return (2);
		}
		i++;
	}
	return (0);
}

int	n_position(char *str, char c)
{
	int	i;
	int	error;

	i = 0;
	if (str[0] >= '0' && str[0] <= '9')
		return (1);
	while (str[i])
	{
		error = spchar(str, i);
		if (error != 3)
			return (error);
		else if (str[i] == c)
		{
			if (!str[i + 1])
				return (1);
			return (2);
		}
		i++;
	}
	return (0);
}

int	export_error(char *str, int error)
{
	if (error == 2)
		printf("minishell: %s: event not found\n", str);
	else
		printf("minishell: export: '%s': not a valid identifier\n", str);
	return (error);
}

int	check_exp(char *str)
{
	char	**str2;
	int		pos;

	if (!ft_strcmp(str, "="))
		return (export_error(str, 1));
	if (str[0] == '#')
		return (2);
	else if (str[0] == '=')
		return (export_error(str, 1));
	str2 = ft_split(str, '=', 0);
	pos = n_position(str2[0], '!');
	if (pos == -1 && !str2[1])
		return (export_error(str, 1));
	if (pos == 1)
		return (export_error(str, 1));
	else if (pos == 2)
		return (export_error(skip_c(str, '!'), 2));
	if (!str2[1])
		return (-1);
	str = skip_c(str, '=');
	if (v_position(str, '!'))
		return (export_error(skip_c(str, '!'), 2));
	return (0);
}
