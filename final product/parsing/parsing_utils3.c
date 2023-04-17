/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:04:40 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/15 12:22:53 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_filecomand(t_lexer **lexer, t_ast **aux, int check, t_ast **node)
{
	if (check == command)
	{
		if (!aux)
			(*node)->command = treat_string(lexer, NULL, node);
		else
			(*node)->command = treat_string(lexer, aux, node);
	}
	else
		(*node)->command = NULL;
	if (check == file)
		(*node)->file = ft_strdup((*lexer)->str);
	else
		(*node)->file = NULL;
}

t_ast	*create_treenode(t_lexer **lexer, t_ast **aux, int check)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (node)
	{
		node->node = (*lexer)->number;
		node->type = check;
		find_filecomand(lexer, aux, check, &node);
		node->left = NULL;
		node->rigth = NULL;
		if (aux)
			node->prev = *aux;
		else
			node->prev = NULL;
	}
	return (node);
}

void	passing_file(t_lexer **lexer)
{
	while (is_file((*lexer)->type))
	{
		*lexer = (*lexer)->next;
		*lexer = (*lexer)->next;
		if ((*lexer)->next == NULL)
			break ;
	}
}

int	leftnode_file(t_lexer **lexer, t_ast **tree, int i)
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
			return (0);
	}
	return (0);
}

int	when_file(t_lexer **lexer, t_ast **tree)
{
	int	i;

	i = (*lexer)->number;
	if ((*tree)->left == NULL)
    {
        if (leftnode_file(lexer, tree, i)) 
            return (2);
    }
	if ((*tree)->rigth == NULL && (*tree)->left->node != (*lexer)->number)
	{
		(*tree)->rigth = create_treenode(lexer, tree, command);
		return (0);
	}
	else if ((*tree)->rigth != NULL)
		*tree = (*tree)->rigth;
	return (0);
}
