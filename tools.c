/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:34:38 by sfarhan           #+#    #+#             */
/*   Updated: 2022/07/26 23:03:46 by oel-berh         ###   ########.fr       */
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
