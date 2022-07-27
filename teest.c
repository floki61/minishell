
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write (fd, &s[i], 1);
			i++;
		}
	}
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

int main()
{
    int fd;

    fd = open("file", O_RDWR | O_CREAT | O_TRUNC, 0644);
    read_from_0("end",fd);
}