/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:04:40 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/13 17:06:19 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int	parsing_str(t_lexer **lexer, t_ast **tree)
{
	int	i;

	while (*lexer)
	{
		if (is_file((*lexer)->type) || (*lexer)->type == pipem)
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
		if ((!is_file((*lexer)->type)) && (*lexer)->next == NULL)
			return (error_syntax("'newline'", 2));
		while ((*tree)->prev != NULL)
			*tree = (*tree)->prev;
		while (*lexer)
		{
			if ((*lexer)->number != (*tree)->node && (*lexer)->type != pipem && is_file((*tree)->type))
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
					if (is_file((*lexer)->type))
					{
						while (is_file((*lexer)->type))
						{
							*lexer = (*lexer)->next;
							*lexer = (*lexer)->next;
							if ((*lexer)->next == NULL)
								break ;
						}
					}
				}
				else if ((*tree)->rigth == NULL && (*lexer)->number > (*tree)->node)
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
	return (0);
}