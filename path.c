/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarhan <sfarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:02:03 by sfarhan           #+#    #+#             */
/*   Updated: 2022/06/28 18:57:27 by sfarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
}

// static  int	search_path(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (!(strncmp(env[i], "PATH", 4)))
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }

// char	**get_path(char *env)
// {
// 	int		i;
// 	char	**path;
// 	// char	**equal;

// 	// i = search_path(env);
// 	// equal = ft_split(env, '=', &i);
// 	path = ft_split(env, ':', &i);
// 	// printf("%s\n",path[0]);
// 	// free_tab(equal);
// 	return (path);
// }

// int		lets_check(char *str)
// {
// 	int  i;
// 	char **cmd_op;
// 	char **path;
// 	char *env;
// 	char  *cmd_path;
	
// 	i = 0;
// 	env = NULL;
// 	env = getenv("PATH");
// 	cmd_op = ft_split(str, ' ', &i);
// 	if (access(str, F_OK) == 0)
// 		execve(cmd_op[0], cmd_op, &env);
// 	path = get_path(env);
// 	// 	printf("hey\n");
// 	// printf("%s\n",path[0]);
// 	i = 0;
// 	while (path[i])
// 	{
// 		// printf("%s\n",path[i]);
// 		cmd_path = ft_strjoin(path[i], "/");
// 		cmd_path = ft_strjoin(cmd_path, cmd_op[0]);
// 		printf("%s\n",cmd_path);
// 		if (access(cmd_path, F_OK) == 0)
// 			execve(cmd_path, cmd_op, &env);
// 		free(cmd_path);
// 		i++;
// 	}
// 	return (0);
// }