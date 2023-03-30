/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:02:57 by idias-al          #+#    #+#             */
/*   Updated: 2023/03/30 08:29:35 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**array_string(char **new)
{
	
}

char	**treat_string(char **str, t_ast *aux, int i)
{
	char	**new;
	int		words;
	int		j;

	j = 0;
	if (!aux)
		return (str);
	if (i < aux->node && aux->type == pipem)
	{
		new = (char **)malloc(sizeof(char **) * (aux->node - i));
		while (i < aux->node)
		{	
			new[j] = ft_strdup(str[i]);
			i++;
			j++;
		}
	}
	else if (i > aux->node && aux->type == pipem)
	{
		if (!aux->rigth)
		{
			new = (char **)malloc(sizeof(char **) * (i - aux->node + 1));
			i = aux->node + 1; 
			while (str[i])
			{
				new[j] = ft_strdup(str[i]);
				i++;
				j++;
			}
		}
	}
	else if (aux->type == red_in && i > aux->node)
	{
		new = (char **)malloc(sizeof(char **) * (i - aux->node));
		i = aux->node + 2;
		while (str[i])
		{
			new[j] = ft_strdup(str[i]);
			i++;
			j++;
		}
	}
	else if (aux->type == red_out && i < aux->node)
	{
		new = (char **)malloc(sizeof(char **) * (aux->node - i));
		while (str[i])
		{
			new[j] = ft_strdup(str[i]);
			i++;
			j++;
		}
	}
	return (new);
}

t_ast	*create_treenode(char **str, int check, int i, t_ast *aux)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (node)
	{
		node->node = i;
		node->type = check;
		if (check == 3)
			node->command = treat_string(str, aux, i);
		else
			node->command = NULL;
		if (check == 4)
			node->file = str[i];
		else
			node->file = NULL;
		node->left = NULL;
		node->rigth = NULL;
		node->prev = NULL;
	}
	return (node);
}

void	print_tree(t_ast *node, int i, char **str)
{
	int j;
	int	a;

	j = i;
	a = 0;
	while (j > 0)
	{
		printf("\t");
		j--;
	}
	j = 0;
	if (node->command)
	{
		printf("node_check: %d, ", node->type);
		printf("node->command:");
		while (node->command[a])
		{
			printf(" %s", node->command[a]);
			a++;
		}
		printf("\n");
	}
	else
		printf("node_check: %d, node->str: %s\n", node->type, str[node->node]);		
	i++;
	if (node->left)
	{
		while (i > j)
		{
			printf("\t");
			j++;
		}
		j = 0;
		printf("left node\n");
		print_tree(node->left, i, str);
	}
	if (node->rigth)
	{
		while (i > j)
		{
			printf("\t");
			j++;
		}
		j = 0;
		printf("rigth node\n");
		print_tree(node->rigth, i, str);
	}
}

void	parsing_str(char **str)
{
	t_ast	*node;
	int	i;
	int j;

	i = 0;
	node = NULL;
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
	if (node)
		while (node->prev)
			node = node->prev;
	i = 0;
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
				}
				else
				{
					node = node->rigth;
					node->left = create_treenode(str, command, i, node);
					i = node->node;
				}
			}
		}
		else if (node->type == red_in && i != node->node)
		{
			if (!node->left)
				node->left = create_treenode(str, file, i, node);
			else if (!node->rigth)
				node->rigth = create_treenode(str, command, i, node);
			if (node->rigth)
				node = node->rigth;
		}
		i++;
	}
	while (node->prev)
		node = node->prev;
	print_tree(node, 0, str);
}

int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	char **str;
	int i;

	i = 0;
	while (1)
	{
		line = readline("\033[1;31m prompt: \033[0m");
		str = ft_split(line,' ');
		if (!ft_strncmp(str[i], "exit", 4))
			exit(EXIT_SUCCESS);
		parsing_str(str);
		i = 0;
		add_history(line);
	}
}
