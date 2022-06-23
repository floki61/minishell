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
	char *cwd;
	char *dir;

	cwd = malloc(sizeof(char) * 1000);
	getcwd(cwd, sizeof(char) * 1000);
	dir = ft_lastcar(cwd, '/');
	printf("-> %s",dir);
}

void	ft_read()
{
	int		size;
	char 	**arg;
	char	*inpt;

	size = 0;
	inpt = readline(" ");
	arg	 = ft_split(inpt,' ',&size);
	// if(size == 1)
	// 	lets_check(inpt);
}
int main()
{
	while(1)
	{
		printdir();
		ft_read();
	}
	return (0);
}