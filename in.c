#include "stdio.h"
#include "stdlib.h"

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

char	*ft_strjoin(char	*s1, char	*s2)
{
	char	*ret;
	int		i;
	int		str1;
	int		str2;
	int		strr1;

	i = -1;
	str1 = ft_strlen(s1);
	str2 = ft_strlen(s2);
	ret = (char *) malloc(sizeof(char) * (str1 + str2 + 1));
	if (!ret)
	{
		free (ret);
		return (NULL);
	}
	if (s1)
		while (s1[++i])
			ret[i] = s1[i];
	strr1 = str1;
	i = 0;
	while (s2[i])
		ret[str1++] = s2[i++];
	ret[strr1 + str2] = '\0';
	// free(s1);
	return (ret);
}

int main(int argc,char **argv, char **env)
{
    *env = ft_strjoin(*env, "\nadd_this");
    int i = 0;
    while(env[i])
    {
        printf("env: %s\n",env[i]);
        i++;
    }
}