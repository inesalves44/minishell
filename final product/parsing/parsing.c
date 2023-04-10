/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:04:40 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/10 20:25:38 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_file(t_lexer **lexer, t_ast *node)
{
	while (*lexer)
	{
		if ((*lexer)->number == node->node + 1)
			return (0);
		*lexer = (*lexer)->next;
	}
	return (error_syntax("'newline'", 2));
}

int	pipes_lexer(t_lexer *lexer)
{
	int	p;

	p = 0;
	while (lexer->prev)
		lexer = lexer->prev;
	while (lexer)
	{
		if (lexer->type == pipem)
			p++;
		if (!lexer->next)
			break ;
		lexer = lexer->next;
	}
	return (p);
}

int	checking_nodes(t_ast *tree, t_lexer *lexer, int i)
{
	int	max;
	int red;
	int start;
	
	max = 0;
	red = 0;
	start = lexer->number;
	if (i == 1 || i == 3)
	{
		while (lexer->next)
		{
			max++;
			if (lexer->type != 0 && lexer->type != 82 && lexer->type != 82)
				red += 2;
			lexer = lexer->next;
		}
		max++;
		max = max - red;
	}
	else if (i == 2)
	{
		while (tree->type != pipem)
			tree = tree->rigth;
		while (lexer->number != tree->node)
		{
			if (lexer->type != 0 && lexer->type != 82 && lexer->type != 82)
				red += 2;
			lexer = lexer->next;
		}
		max = tree->node - red - start;
	}
	return (max);
}

int	length_lexer(t_lexer *lexer, t_ast *aux, int i)
{
	int	len;

	len = 0;
	if (i == 0)
	{
		while (lexer->next)
		{
			len++;
			lexer = lexer->next;
		}
		len++;
	}
	else
		len = checking_nodes(aux, lexer, i);
	return (len);
}

char	**create_array(t_lexer **lexer, int len, t_ast **tree)
{
	int		j;
	char	**new;

	j = 0;
	new = (char **)malloc(sizeof(char *) * (len + 1));
	(*tree)->dquotes = (int *)malloc(sizeof(int) * len);
	(*tree)->squotes = (int *)malloc(sizeof(int) * len);
	while (j < len)
	{
		if ((*lexer)->type == red_in || (*lexer)->type == red_out || (*lexer)->type == here_doc || (*lexer)->type == app_out)
		{
			while ((*lexer)->type == red_in || (*lexer)->type == red_out || (*lexer)->type == here_doc || (*lexer)->type == app_out)
			{
				*lexer = (*lexer)->next;
				*lexer = (*lexer)->next;
				if ((*lexer)->next == NULL)
					break ;
			}
		}
		new[j] = ft_strdup((*lexer)->str);
		if ((*lexer)->type == 82)
		{
			(*tree)->dquotes[j] = j;
			(*tree)->squotes[j] = -1;
		}
		else if ((*lexer)->type == 87)
		{
			(*tree)->squotes[j] = j;
			(*tree)->dquotes[j] = -1;
		}
		else
		{
			(*tree)->squotes[j] = -1;
			(*tree)->dquotes[j] = -1;
		}
		if ((*lexer)->next == NULL || j == len - 1)
		{
			j++;
			if ((*lexer)->next != NULL)
				*lexer = (*lexer)->next;
			if ((*lexer)->type == red_in || (*lexer)->type == red_out || (*lexer)->type == here_doc || (*lexer)->type == app_out)
			{
				while ((*lexer)->type == red_in || (*lexer)->type == red_out || (*lexer)->type == here_doc || (*lexer)->type == app_out)
				{
					*lexer = (*lexer)->next;
					*lexer = (*lexer)->next;
					if ((*lexer)->next == NULL)
						break ;
				}
			}
			break;
		}
		(*lexer) = (*lexer)->next;
		j++;
	}
	new[j] = 0;
	return (new);
}

char	**treat_string(t_lexer **lexer, t_ast **aux, t_ast **tree)
{
	char	**new;
	int		len;
	
	new = NULL;
	if (aux == NULL)
	{
		len = length_lexer(*lexer, NULL, 0);
		new = create_array(lexer, len, tree);
	}
	else
	{
		if (!pipes_lexer(*lexer))
			len = length_lexer(*lexer, *aux, 1);
		else
		{
			if ((*aux)->left == NULL)
				len = length_lexer(*lexer, *aux, 2);
			else
				len = length_lexer(*lexer, *aux, 3);
		}
		new = create_array(lexer, len, tree);
	}
	return (new);
}

t_ast	*create_treenode(t_lexer **lexer, t_ast **aux, int check)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (node)
	{
		node->node = (*lexer)->number;
		node->type = check;
		if (check == command)
		{
			if (!aux)
				node->command = treat_string(lexer, NULL, &node);
			else
				node->command = treat_string(lexer, aux, &node);
		}
		else
			node->command = NULL;
		if (check == file)
			node->file = ft_strdup((*lexer)->str);
		else
			node->file = NULL;
		node->left = NULL;
		node->rigth = NULL;
		if (aux)
			node->prev = *aux;
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
			printf(" %s;", node->command[a]);
			printf("dquotes %d, ", node->dquotes[a]);
			printf("squotes %d, ", node->squotes[a]);
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

int	parsing_str(t_lexer **lexer, t_ast **tree)
{
	int	i;

	while (*lexer)
	{
		if ((*lexer)->type != 0 && (*lexer)->type != 82 && (*lexer)->type != 87)
		{
			if (*tree == NULL)
				*tree = create_treenode(lexer, NULL, (*lexer)->type);
			else
				(*tree)->rigth = create_treenode(lexer, tree, (*lexer)->type);
		}
		if (*tree && (*tree)->rigth)
		{
			(*tree)->rigth->prev = *tree;
			*tree = (*tree)->rigth;
		}
		if ((*lexer)->next == NULL)
			break ;
		*lexer = (*lexer)->next;
	}
	while ((*lexer)->prev != NULL)
		*lexer = (*lexer)->prev;
	if (*tree == NULL)
		*tree = create_treenode(lexer, NULL, command);
	else
	{
		if (((*lexer)->type != 0 || (*lexer)->type != 82 || (*lexer)->type != 87 || (*lexer)->type != pipem) && (*lexer)->next == NULL)
			return (error_syntax("'newline'", 2));
		while ((*tree)->prev != NULL)
			*tree = (*tree)->prev;
		while (*lexer)
		{
			if ((*lexer)->number != (*tree)->node && (*lexer)->type != pipem && ((*tree)->type == red_in || (*tree)->type == red_out || (*tree)->type == here_doc || (*tree)->type == app_out))
			{
				i = (*lexer)->number;
				if ((*tree)->left == NULL)
				{
					if (get_file(lexer, *tree))
						return (2);
					(*tree)->left = create_treenode(lexer, tree, file);
					if (i != (*lexer)->number)
					{
						while ((*lexer)->number != i)
							*lexer = (*lexer)->prev;	
					}
					else
					{
						if ((*lexer)->next != NULL)
							*lexer = (*lexer)->next;
						else
							break ;	
					}
				}
				if ((*tree)->rigth == NULL && (*tree)->left->node != (*lexer)->number)
				{
					(*tree)->rigth = create_treenode(lexer, tree, command);
					break ;
				}
				else if ((*tree)->rigth != NULL)
					*tree = (*tree)->rigth;
			}
			else if ((*lexer)->number != (*tree)->node && (*tree)->type == pipem)
			{
				if ((*tree)->left == NULL && (*lexer)->number < (*tree)->node)
				{
					(*tree)->left = create_treenode(lexer, tree, command);
						*lexer = (*lexer)->next;
				}
				if ((*tree)->rigth == NULL && (*lexer)->number > (*tree)->node)
				{
					(*tree)->rigth = create_treenode(lexer, tree, command);
					break ;
				}
				else if ((*tree)->rigth != NULL)
					*tree = (*tree)->rigth;
			}
			else if ((*lexer)->next != NULL)
				*lexer = (*lexer)->next;
			else if ((*lexer)->next == NULL)
				break ;
		}
	}
	while ((*tree)->prev != NULL)
		*tree = (*tree)->prev;
	while ((*lexer)->prev != NULL)
		*lexer = (*lexer)->prev;
	//print_tree(*tree, 0);
	return (0);
}


/*while (tree->prev)
		tree = tree->prev;
	while (tree)
	{
		if (tree->left && tree->left->node > lexer->number && tree->left->node < max)
			max = tree->left->node;
		if (tree->node > lexer->number && tree->node < max)
			max = tree->node;
		if (!tree->rigth)
			break ;
		tree = tree->rigth;
	}*/

	/*if ((*aux)->type == red_in || (*aux)->type == red_out || (*aux)->type == app_out || (*aux)->type == here_doc)
		{
			if ((*lexer)->number < (*aux)->node)
				len = length_lexer(*lexer, *aux, 1);
			else
				len = length_lexer(*lexer, *aux, 0);
			new = create_array(*lexer, len, tree);
		}
		else if ((*aux)->type == pipem)
		{
			if ((*aux)->left == NULL)
			{
				len = length_lexer(*lexer, *aux, 1);
				new = create_array(*lexer, len, tree);
				while ((*lexer)->number != (*aux)->node)
					*lexer = (*lexer)->next;
			}
			else if ((*aux)->rigth == NULL)
			{
				len = length_lexer(*lexer, *aux, 2);
				new = create_array(*lexer, len, tree);
			}
		}*/