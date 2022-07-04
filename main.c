/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 20:42:38 by oel-berh          #+#    #+#             */
/*   Updated: 2022/07/04 02:31:55 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
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
void    printdir()
{
	char *cwd = NULL;
	char *dir;

	cwd = malloc(sizeof(char) * 100);
	getcwd(cwd, sizeof(char) * 1000);
	dir = ft_lastcar(cwd, '/');
	printf("-> %s ",dir);
}

char	*ft_read()
{
	char	*inpt;
	
	inpt = readline("");
	while(if_builtins(inpt) == 1)
	{
		printdir();
		inpt = readline("");
	}
	return (inpt);
}
int if_builtins(char *buf)
{
	if(ft_strncmp(buf,"cd ",3) == 0)
	{
		if(chdir(buf + 3) < 0)
			printf("error3\n");
		return (1);
	}
	if(strcmp(buf,"pwd") == 0 )
	{
		char *cwd;
	
		cwd = malloc(sizeof(char) * 100);
		getcwd(cwd, 100);
		printf("pwd=%s\n",cwd);
		return (1);
	}
	else if(strcmp(buf,"exit") == 0)
	{
		printf("exit\n");
		exit (1);
	}
	// else if(strcmp(buf,"env") == 0)
	return (0);
}

int main(int ac, char **av, char **envp)
{
	int 	fd;
	char	*buf;
	int		c;

	(void)ac;
	(void)av;
	while ((fd = open("test.txt", O_RDWR)) >= 0)
	{
		if (fd >= 3)
		{
			close (fd);
			break;
		}
	}
	while (1)
	{
		printdir();
		buf = ft_read();
		c = 0;
		// if_builtins(buf);
		if (fork() == 0)
			run_cmd(parsecmd(buf), envp, &c);
		wait(0);
	}
	return (0);
}