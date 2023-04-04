while (str[i])
	{
		if (!ft_strncmp(str[i], "|", 1))
		{
			if (!node)
				node = create_treenode(NULL, pipem, i, NULL);
			else
				node->rigth = create_treenode(NULL, pipem, i, node);
		}
		else if (!ft_strncmp(str[i], ">", 1))
		{
			if (!node)
				node = create_treenode(NULL, red_out, i, NULL);
			else
				node->rigth = create_treenode(NULL, red_out, i, node);
		}
		else if (!ft_strncmp(str[i], "<", 1))
		{
			if (!node)
				node = create_treenode(NULL, red_in, i, NULL);
			else
				node->rigth = create_treenode(NULL, red_in, i, node);
		}
		if (node && node->rigth)
		{
			node->rigth->prev = node;
			node = node->rigth;
		}
		i++;
	}

	while (str[i])
	{
		if (!node)
		{
			node = create_treenode(str, command, i, NULL);
			break ;
		}
		if (node->type == pipem && node->node != i)
		{
			if (i < node->node)
			{
				node->left = create_treenode(str, command, i, node);
				node->left->prev = node;
				i = node->node;
			}
			else if (i > node->node)
			{
				if (!node->rigth)
				{
					while (str[i])
						i++;
					i--;
					node->rigth = create_treenode(str, command, i, node);
					node->rigth->prev = node;
				}
				else if (node->rigth->type == pipem)
				{
					node = node->rigth;
					node->left = create_treenode(str, command, i, node);
					node->left->prev = node;
					i = node->node;
				}
				else
				{
					node = node->rigth;
					i--;
				}
			}
		}
		else if ((node->type == red_in || node->type == red_out) && i != node->node)
		{
			if (!node->left)
			{
				j = i;
				i = node->node + 1;
				node->left = create_treenode(str, file, i, node);
				node->left->prev = node;
				i = j - 1;
			}
			else if (i != node->node + 1 && !node->rigth)
			{
				node->rigth = create_treenode(str, command, i, node);
				while (str[i] && node->left)
					i++;
				if (node->left)
					i--;
				if (i < node->node)
					i = node->node;
				node->rigth->prev = node; 
			}
			else if (i != node->node + 1 && node->rigth)
			{
				node = node->rigth;
				i--;
			}
		}
		i++;
	}


	char	*get_file(char **str, t_ast *node)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == node->node)
		{
			i++;
			return (str[i]);
		}
		i++;
	}
	return (NULL);
}

int	checking_nodes(t_ast *node, int j, int i)
{
	int max;
	
	while (node->prev)
		node = node->prev;
	max = j;
	while (node)
	{
		if (node->node < j && node->node > i)
			max = node->node;
		node = node->rigth;
	}
	return (max);
}

char	**treat_string(char **str, t_ast *aux, int i)
{
	char	**new;
	int		words;
	int		j;
	int		max;

	j = 0;
	if (!aux)
		return (str);
	if (i < aux->node && aux->type == pipem)
	{
		max = checking_nodes(aux, aux->node, i);
		new = (char **)malloc(sizeof(char *) * (max - i + 1));
		while (i < max)
		{	
			new[j] = ft_strdup(str[i]);
			i++;
			j++;
		}
		new[j] = 0;
	}
	else if (i > aux->node && aux->type == pipem)
	{
		if (!aux->rigth)
		{
			new = (char **)malloc(sizeof(char *) * (i - aux->node + 1));
			i = aux->node + 1; 
			while (str[i])
			{
				new[j] = ft_strdup(str[i]);
				i++;
				j++;
			}
			new[j] = 0;
		}
	}
	else if (aux->type == red_in || aux->type == red_out)
	{
		if (i < aux->node)
		{
			new = (char **)malloc(sizeof(char *) * (aux->node + 1));
			while (i < aux->node)
			{
				new[j] = ft_strdup(str[i]);
				i++;
				j++;
			}
			new[j] = 0;
		}
		else
		{
			while (str[i])
				i++;
			i--;
			new = (char **)malloc(sizeof(char *) * (i - aux->node));
			i = aux->node + 2;
			while (str[i])
			{
				new[j] = ft_strdup(str[i]);
				i++;
				j++;
			}
			new[j] = 0;
		}
	}
	return (new);
}