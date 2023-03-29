/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:02:57 by idias-al          #+#    #+#             */
/*   Updated: 2023/03/28 19:54:20 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_treenode(char **str, int check, int i)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (node)
	{
		node->node = i;
		node->type = check;
		if (check == 3)
			node->command = str;
		else
			node->command = NULL;
		if (check == 4)
			node->file = str[0];
		else
			node->file = NULL;
		node->left = NULL;
		node->rigth = NULL;
		node->prev = NULL;
	}
	return (node);
}

void	print_tree(t_ast *node, int i)
{
	int j;

	j = i;
	while (j > 0)
	{
		printf("\t");
		j--;
	}
	j = 0;
	printf("node_check: %d, node_id: %d\n", node->type, node->node);
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
		print_tree(node->left, i);
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
		print_tree(node->rigth, i);
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
				node = create_treenode(NULL, pipem, i);
			else
				node->rigth = create_treenode(NULL, pipem, i);
		}
		else if (!ft_strncmp(str[i], ">", 1))
		{
			if (!node)
				node = create_treenode(NULL, red_out, i);
			else
				node->rigth = create_treenode(NULL, red_out, i);
		}
		else if (!ft_strncmp(str[i], "<", 1))
		{
			if (!node)
				node = create_treenode(NULL, red_in, i);
			else
				node->rigth = create_treenode(NULL, red_in, i);
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
			node = create_treenode(str, command, i);
		else if (node->type == pipem)
		{
			if (i < node->node)
				node->left = create_treenode(str, command, i);
			else if (i > node->node && !node->rigth)
				node->rigth = create_treenode(str, command, i);
			if (node->left)
				node->left->prev = node;
			if (node->rigth)
				node->rigth->prev = node;
		}
		i++;
	}
	print_tree(node, 0);
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
