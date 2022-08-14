

int tmp (char **cmd, t_list **data, int i)
{
    int j;
    char **op;
    char *value;
    t_list *tmp;

    tmp = *data;
    j = 0;
    op = ft_split(cmd[i], '=', 0);
	if(op[0][ft_strlen(op[0]) - 1] == '+')
	{
		op[0][ft_strlen(op[0]) - 1] = '\0';
		j++;
	}
	while(tmp)
	{
		if(ft_strcmp(op[0],tmp->name) == 0)
		{
			value = cmd[i];
    	    while(*value != '=')
    	        value++;
			if(!tmp->sep)
				tmp->sep = "=";
			if(j == 1)
				tmp->value = ft_strjoin(tmp->value,++value);
			else
				tmp->value = ++value;
			j = 3;
			break ;
		}
		tmp = tmp->next;
    }
    return (j);
}

int export (char **cmd, t_list **data)
{
    t_list *tmp;
    int i;
    int j;
    char *value;

    i = 1;
    tmp = *data;
    while(cmd[i])
	{
		j = 0;
		tmp = *data;
		while (!exist_sep(cmd[i]))
        {
			sep = withoutsep(cmd[i],data);
            if(sep)
				return(sep);
			if(!cmd[++i])
				return (2);
        }
		sep = check_exp(cmd[i]);
        if(sep)
            return (sep);
		if(cmd[i][0] == '#')
			return (2);
        if(tmp (cmd, data, i) != 3)
		{
			value = cmd[i];
    		while(*value != '=')
    	    	value++;
			ft_lstadd_back(data,ft_lstnew(op[0],++value, "="));
		}
		i++;
	}
	return (2);
}

int	ft_export(char **cmd, t_list **data)
{
	t_list *tmp;
	char	**op;
	char    *value;
	char 	*str;
	int		i;
	int		j;
	int		sep;
	
	i = 1;
	j = 0;
	str = NULL;
	if(!cmd[i] || cmd[i][0] == '#')
	{
		ft_printenv(*data);
		return (2);
	}
    return (export(cmd, data));
}