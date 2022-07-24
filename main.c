/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:53 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/24 00:06:10 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	if(!str)
		return (i);
	while(str[i])
		i++;
	return (i);
}

// return pointer to the name directory
char *ft_lastcar(char *str, char c)
{
	int lent;

	lent = ft_strlen(str);
	while(*str)
		str++;
	while(lent)
	{
		if(*str == c)
		{
			str++;
			return(str);
		}
		lent--;
		str--;
	}
	return(NULL);
}

//printf the name directory
// char *    printdir()
// {
// 	char *cwd;
// 	char *dir;

// 	cwd = malloc(sizeof(char) * 1000);
// 	getcwd(cwd, sizeof(char) * 1000);
// 	dir = ft_lastcar(cwd, '/');
// 	return (dir);
// }



char	*ft_read()
{
	char	*inpt;
	
	inpt = readline("-> minishell ");
	inpt = ft_skip_spaces(inpt);
// 	while(if_builtins(inpt) == 0 || if_dsigne(inpt,envp) == 0)
// 	{
// 		inpt = readline("-> minishell ");
// 		inpt = ft_skip_spaces(inpt);
// 	}
	return (inpt);
}

int main(int ac, char **av, char **envp)
{
	char	*buf;
	// char	*env;
	int		c;

	(void)ac;
	(void)av;
	// env = NULL;
	while (1)
	{
		c = 0;
		buf = ft_read();
		if (fork() == 0)
			run_cmd(parsecmd(buf), envp, &c);
		// printf("[exmain]: %s\n",*envp);
		wait(0);
	}
	return (0);
}