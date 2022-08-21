/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 01:19:30 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/21 04:50:02 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **inpt)
{
	char	*cwd;
	int		i;
	int		n;

	cwd = NULL;
	i = 1;
	n = 0;
	while (inpt[i])
	{
		if (v_position(inpt[i], '!') == 2)
		{
			while (*inpt[i] != '!')
				inpt[i]++;
			fperror(inpt[i], ":event not found\n");
			return (2);
		}
		i++;
	}
	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	return (2);
}

int	bult_1(char	**inpt)
{
	if (ft_strcmp(inpt[0], "echo") == 0)
		return (ft_echo(inpt));
	else if (ft_strcmp(inpt[0], "pwd") == 0)
		return (ft_pwd(inpt));
	return (0);
}

int	bult_2(char	**inpt, t_list **data)
{
	if (ft_strcmp(inpt[0], "env") == 0)
		return (printenvp(inpt, data));
	else if (ft_strcmp(inpt[0], "export") == 0)
		return (ft_export(inpt, data));
	else if (ft_strcmp(inpt[0], "unset") == 0)
		return (ft_unset(inpt, data));
	else if (ft_strcmp(inpt[0], "cd") == 0)
		return (ft_cd(inpt, data));
	return (0);
}

int	if_builtins(char **inpt, t_list **data)
{
	int	status;

	status = bult_1(inpt);
	if (status)
		return (status);
	else
	{
		status = bult_2(inpt, data);
		if (status)
			return (status);
	}
	return (0);
}

int	ifenv(t_cmd *cmd, t_list **data)
{
	t_exec	*exe;
	int		bult;

	if (cmd == 0)
		return (0);
	if (cmd->type != EXEC)
		return (0);
	exe = (t_exec *)cmd;
	if (exe->args[0] == 0)
		return (0);
	bult = bult_2(exe->args, data);
	if (bult)
	{
		if (bult == 2)
			g_exit_status = 0;
		else
			g_exit_status = bult;
		return (bult);
	}
	return (0);
}
