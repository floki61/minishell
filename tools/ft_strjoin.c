/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:01:42 by sfarhan           #+#    #+#             */
/*   Updated: 2022/08/30 08:25:55 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	i = -1;
	j = 0;
	ret = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
	{
		free (ret);
		return (NULL);
	}
	if (s1)
		while (s1[++i])
			ret[j++] = s1[i];
	i = 0;
	if (s2)
		while (s2[i])
			ret[j++] = s2[i++];
	ret[j] = '\0';
	return (ret);
}

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*f;

	if (length == 0)
	{
		return (0);
	}
	s = (unsigned char *)second;
	f = (unsigned char *)first;
	i = 0;
	while ((f[i] != '\0' || s[i] != '\0') && (f[i] == s[i]) && (i < length - 1))
	{
		i++;
	}
	return (f[i] - s[i]);
}

int	ft_limites(char *str)
{
	if (ft_strncmp(str, "|", 1) == 0)
		return (1);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

t_cmd	*which_redir(t_cmd *cmd, char *clear, int token, char *q)
{
	if (token == '<')
		cmd = redirect(cmd, clear, O_RDONLY, 0);
	else if (token == '>')
		cmd = redirect(cmd, clear, O_WRONLY | O_CREAT | O_TRUNC, 1);
	else if (token == '+')
		cmd = redirect (cmd, clear, O_WRONLY | O_CREAT | O_APPEND, 1);
	else if (token == '-')
	{
		free (clear);
		cmd = redirect (cmd, clean(q), 3, 0);
	}
	return (cmd);
}
