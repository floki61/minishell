/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:12:54 by oel-berh          #+#    #+#             */
/*   Updated: 2022/08/12 20:48:42 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int status_exit(char *str)
{
	long long status;
	
	status = atoi(str);
	if(status < 0)
	{
		if((status += 256) < 0)
			status = status_exit(ft_itoa(status));
	}
	else
		if(status >= 256)
			if((status -= 256) >= 256)
				status =  status_exit(ft_itoa(status));
	return (status);
}

int	numeric_status(char *str)
{
	int i;

	i = 0;
	if(str[i] == '-')
		i++;
	while(str[i])
	{
		if(str[i] < '0' || str[i] > '9')
			return(0);
		i++;
	}
	return(1);
}

int	ifexit(t_cmd	*cmd)
{
	t_exec	*exe;
	// int status;

	if(cmd->type == EXEC)
	{
		exe = (t_exec *)cmd;
		if (exe->args[0] == 0)
			return (0);
		if(ft_strcmp(exe->args[0],"exit") == 0)
		{	
			printf("exit\n");
			if(exe->args[1])
			{
				if(!numeric_status(exe->args[1]))
				{
					printf("minishell: exit: %s: numeric argument required\n",exe->args[1]);
					exit (255);
				}
				else
				{
					if(exe->args[2])
					{
						printf("minishell: exit: too many arguments\n");
						exit_status = 1;
						return (1);
					}
					else
						exit (status_exit(exe->args[1]));
					// printf("exit_status: %d\n",exit_status);
				}
			}
			else
				exit(0);	
		}
	}
	return 0;
}
int	ifenv(t_cmd *cmd ,t_list	**data, char **path)
 {
	t_exec	*exe;
	int bult;
	
	path = NULL;
	if(cmd->type != EXEC)
		return 0;
	exe = (t_exec *)cmd;
	if (exe->args[0] == 0)
		return 0;
	bult = bult_2(exe->args, data);
	if(bult)
	{
		if(bult == 2)
			exit_status = 0;
		else
			exit_status = bult;
		return(bult);
	}
	return(0);
 }
 