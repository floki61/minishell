#include "stdio.h"
#include "stdlib.h"
#include "minishell.h"

typedef struct t_list
{
	char *name;
	char *value;
	struct t_list *next;
} 	t_list;

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	new->next = NULL;
	if (!*alst)
		*alst = new;
	else
		(ft_lstlast(*alst))->next = new;
}

t_list	*ft_lstnew(void *name,void *value)
{
	t_list	*new;

	new = (t_list *) malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

int main(int argc,char **argv, char **env)
{
	int i = 0;
  	char **op;
	char **op2;
	t_list *data;

	data = NULL;
  	while(env[i])
   	{
		op = ft_split(env[i], '=');
		ft_lstadd_back(&data,ft_lstnew(op[0],op[1]));
		i++;
   	}
	while(data)
	{
		printf("%s=%s\n",data->name,data->);
		data = data->next;
	}

}