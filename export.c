/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 01:00:44 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/15 04:11:31 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
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
	printf("whitoutsep\n");
	ft_lstadd_back(data, ft_lstnew(cmd, NULL, NULL));
	return (0);
}

int	existkey(char *cmd, char **op, t_list **data, char c)
{
	t_list	*tmp;

	tmp = *data;
	while (tmp)
	{
		if (!ft_strcmp(op[0], tmp->name))
		{
			cmd = skip_c(cmd, '=');
			if (!tmp->sep)
				tmp->sep = "=";
			if (c == '+')
				tmp->value = ft_strjoin(tmp->value, ++cmd);
			else
				tmp->value = ++cmd;
			return (2);
		}
		tmp = tmp->next;
	}
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
	ft_lstadd_back(data, ft_lstnew(op[0], ++value, "="));
	//free
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
