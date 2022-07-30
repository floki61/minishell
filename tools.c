/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:34:38 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/30 01:38:37 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	much_to_skip(const char *str, int i)
{
	int		cnt;
	char	*s;

	s = (char *)str;
	cnt = 0;
	printf ("much %c , %d\n", s[i], i);
	i++;
	while (s[i] != 1 && s[i])
	{
		i++;
		cnt++;
	}
	i++;
	return (i);
}

void	read_from_0(char *limitter, int fd)
{
	char	*instruction;

	instruction = NULL;
	while ((instruction = readline("pipe herdoc> ")))
	{
		if (strcmp(limitter, instruction) == 0)
		{
			close(0);
			close(fd);
			return ;
		}
		ft_putstr_fd(instruction, fd);
		ft_putstr_fd("\n", fd);
		free(instruction);
	}
}

int		ft_count(t_list **data)
{
	int		i;
	t_list	*tmp;
	
	i	= 0;
	tmp = *data;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**ft_convert(t_list **data, int count)
{
	int		i;
	t_list	*tmp;
	char 	**env;

	i 	= 0;
	tmp = *data;
	env = malloc(sizeof(char *) * (count + 1));
	while(tmp)
	{
		env[i]	= tmp->name;
		env[i] 	= ft_strjoin(env[i], "=");
		env[i]	= ft_strjoin(env[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
