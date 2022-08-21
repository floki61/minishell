/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 03:07:35 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/21 04:50:13 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fexit_status(char *str)
{
	long long	status;

	status = ft_atoi(str);
	if (status == -1)
	{
		printf("minishell: exit: %s: numeric argument required\n", str);
		exit (255);
	}
	if (status < 0)
	{
		status *= -1;
		status = 256 - (status % 256);
	}
	else
		if (status >= 256)
			status = status % 256;
	return (status);
}

int	numeric_status(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	find_status(t_exec *exe)
{
	if (!numeric_status(exe->args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", exe->args[1]);
		exit (255);
	}
	else
	{
		if (exe->args[2])
		{
			printf("minishell: exit: too many arguments\n");
			g_exit_status = 1;
		}
		else
			exit (fexit_status(exe->args[1]));
	}
	return (1);
}

int	ifexit(t_cmd *cmd)
{
	t_exec	*exe;

	if (cmd == 0)
		return (0);
	if (cmd->type != EXEC)
		return (0);
	exe = (t_exec *)cmd;
	if (exe->args[0] == 0)
		return (0);
	if (ft_strcmp(exe->args[0], "exit") == 0)
	{	
		printf("exit\n");
		if (exe->args[1])
			return (find_status(exe));
		else
			exit(0);
	}
	return (0);
}
