/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:53 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/27 10:11:08 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if(!str)
		return(i);
	while (str[i])
		i++;
	return (i);
}

// return pointer to the name directory
char	*ft_lastcar(char *str, char c)
{
	int	lent;

	lent = ft_strlen(str);
	while (*str)
		str++;
	while (lent)
	{
		if (*str == c)
		{
			str++;
			return (str);
		}
		lent--;
		str--;
	}
	return (NULL);
}

void	handle_c(int sig)
{
	if (sig == 2)
	{
		printf ("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_d(int sig)
{
	if (sig == 11)
	{
		rl_replace_line("", 0);
		// printf ("exit\n");
		rl_redisplay();
		exit(0);
	}
}

void	handle_s(int sig)
{
	if (sig == 3)
	{
		printf ("-> minishell ");
		rl_replace_line("", 0);
		//rl_redisplay();
	}
}

char	*ft_read(void)
{
	char	*inpt;

	inpt = readline("\e[0;31m.ᴍɪɴɪꜱʜᴇʟʟ\e[0m ");
	inpt = ft_skip_spaces(inpt);
	return (inpt);
}

int	main(int ac, char **av, char **envp)
{
	char	*buf;
	int		c;
	t_list 	*data;
	char	*limiter;

	limiter = NULL;
	(void) ac;
	(void) av;
	data = NULL;
	signal (SIGINT, handle_c);
	//signal (SIGSEGV, handle_d);
	signal (SIGQUIT, handle_s);
	while (1)
	{
		c = 0;
		buf = ft_read();
		add_history(buf);
		if (fork() == 0)
			(run_cmd(parsecmd(buf, envp), envp, &c, &limiter, &data));
		wait(0);
		printf("c == %d\n",c);
		if(c == 89)
		{
			printf("her\n");
			exit (0);
		}
		printf("hna\n");
		unlink("/tmp/.fd");
	}
	return (0);
}

// export omar=90=op ✓
//export !omar=90
// export omar+=78
//export all=""		✓
//export omar=   >>> env: omar=    export: omar="" ✓
//unset PATH => ls output:""

//exit


// !dm=90 		!dm=90: event not found ✓
// d!m=67       !m=67: event not found ✓
// dm!=90		export: `dm!=90': not a valid identifier ✓


// dm=45!		✓
// dm=!45       dm=!45: event not found ✓
// dm=4!5       dm=!45: event not found ✓

// bash-3.2$ export tio=!23!me!45
// bash: !me!45: event not found    