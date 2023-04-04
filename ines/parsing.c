/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:04:40 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/04 02:37:37 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_file(t_lexer *lexer, t_ast *node)
{
	int	i;

	i = 0;
	while (lexer)
	{
		if (lexer->number == node->node + 1)
			return (lexer->str);
		lexer = lexer->next;
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

int	length_lexer(t_lexer *lexer, t_ast *aux, int i)
{
	int	len;
	int a;

	len = 0;
	if (!aux)
	{
		while (lexer->next)
		{
			len++;
			lexer = lexer->next;
		}
		len++;
		return (len);
	}
	if (aux->rigth)
		a = aux->rigth->node - aux->node;
	else
	{
		while (lexer->next)
		{
			len++;
			lexer = lexer->next;
		}
		len++;
	}
	return (len);
}

char	**create_array(t_lexer *lexer, int len)
{
	int		j;
	char	**new;

	j = 0;
	new = (char **)malloc(sizeof(char *) * (len + 1));
	while (j < len)
	{
		new[j] = ft_strdup(lexer->str);
		lexer = lexer->next;
		j++;
	}
	new[j] = 0;
	return (new);
}

char	**treat_string(t_lexer *lexer, t_ast *aux, int i)
{
	char	**new;
	int		j;
	int		len;
	
	j = 0;
	if (!aux)
		len = length_lexer(lexer, aux, i);
	else
	{
		if (aux->type == red_in || aux->type == red_out || aux->type == app_out || aux->type == here_doc)
		{
			if (lexer->number < aux->node)
				len = aux->node - lexer->number;
			else
				len = length_lexer(lexer, aux, i);
		}
	}
	new = create_array(lexer, len);
	return (new);
}

t_ast	*create_treenode(t_lexer *lexer, t_ast *aux, int i, int check)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (node)
	{
		node->node = lexer->number;
		node->type = lexer->type;
		if (check == command)
			node->command = treat_string(lexer, aux, i);
		else
			node->command = NULL;
		if (check == file)
			node->file = ft_strdup(get_file(lexer, aux));
		else
			node->file = NULL;
		node->left = NULL;
		node->rigth = NULL;
		if (aux)
			node->prev = aux;
		else
			node->prev = NULL;
	}
	return (node);
}

void	print_tree(t_ast *node, int i)
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
	else if (node->file)
	{
		printf("node file: %s\n", node->file);
	}
	else
		printf("node_check: %d\n", node->type);		
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

int	lexer_length(t_lexer *lexer)
{
	int	len;

	len = 0;
	while (lexer->prev)
		lexer = lexer->prev;
	while (lexer)
	{
		len++;
		if (!lexer->next)
			break;
		lexer = lexer->next;
	}
	return (len);
}

t_ast	*parsing_str(t_lexer *lexer)
{
	t_ast	*tree;
	int	i;
	int j;

	tree = NULL;
	while (lexer)
	{
		if (lexer->type != 0 && lexer->type != 82 && lexer->type != 87)
		{
			if (!tree)
				tree = create_treenode(lexer, NULL, lexer->number, lexer->type);
			else
				tree->rigth = create_treenode(lexer, tree, lexer->number, lexer->type);
		}
		if (tree && tree->rigth)
		{
			tree->rigth->prev = tree;
			tree = tree->rigth;
		}
		if (!lexer->next)
			break ;
		lexer = lexer->next;
	}
	while (lexer->prev)
		lexer = lexer->prev;
	if (!tree)
		tree = create_treenode(lexer, NULL, lexer->number, command);
	else
	{
		if (tree)
			while (tree->prev)
				tree = tree->prev;
		while (lexer)
		{
			if (lexer->number != tree->node && (tree->type == red_in || tree->type == red_out || tree->type == here_doc || tree->type == app_out))
			{
				if (!tree->left && lexer->number == tree->node + 1)
					tree->left = create_treenode(lexer, tree, lexer->number, file);
				else if (!tree->rigth && lexer_length(lexer) > 2)
					tree->rigth = create_treenode(lexer, tree, lexer->number, command);
			}
			if (!lexer->next)
				break ;
			lexer = lexer->next;
		}
	}
	while (tree->prev)
		tree = tree->prev;
	print_tree(tree, 0);
	return (tree);
}