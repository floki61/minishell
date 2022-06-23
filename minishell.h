#ifndef MINISHELL_H
#define MINISHELL_H

# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include "string.h"
# include<readline/readline.h>
# include<readline/history.h>

int	    ft_strlen(char *str);
char	*ft_strjoin(char	*s1, char	*s2);
char	**ft_split(char const *s, char c, int *size);
char	**get_path(char *env);
int		lets_check(char *str);

#endif