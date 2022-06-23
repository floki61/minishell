#include "minishell.h"

static int	count(const char *str, char c,int *size)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0' && str[i] != c)
		{
			while (str[i] != '\0' && str[i] != c)
				i++;
			len++;
		}
	}
	*size = len;
	return (len);
}

static int	ft_second(const char *str, int i, char c)
{
	int		cnt;
	char	*s;

	s = (char *)str;
	cnt = 0;
	while (s[i] != c && s[i])
	{
		i++;
		cnt++;
	}
	return (cnt);
}

static char	**set_array(char const *s, char c, int i, char **tab)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	while (s[i])
	{
		k = 0;
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			tab[j] = malloc(ft_second(s, i, c) + 1);
			if (!tab[j])
				return (NULL);
			while (s[i] != c && s[i])
			{
				tab[j][k++] = s[i];
				i++;
			}
			tab[j++][k] = '\0';
		}
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c, int *size)
{
	int		i;
	char	**tab;

	tab = NULL;
	i = 0;
	if (!s)
		return (NULL);
	if (c == '\0' || count(s, c, size) == 0)
	{
		tab = malloc(1 * sizeof(char *));
		tab[0] = NULL;
		return (tab);
	}
	tab = malloc(sizeof(char *) * (count(s, c, size) + 1));
	if (!tab)
		return (NULL);
	return (set_array(s, c, i, tab));
}