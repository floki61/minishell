
#include "minishell.h"

char **parseexp(char *str)
{
    char **op;
    int i = 0;

    op = ft_split(str,'\n');
    while(op[i])
    {
        printf("op: %s\n",op[i]);
        i++;
    }
    return(op);
}

int main(int argc, char **envp)
{
    char *str;
    char **str2;

    str = "hmad=0\nsaid=1\n";
    str2 = parseexp(envp[8]);
    
}