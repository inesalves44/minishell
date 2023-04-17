/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:04:40 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/15 12:37:00 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	first_objects(t_lexer **lexer, t_ast **tree)
{
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
	return (0);
}

int	when_pipe(t_lexer **lexer, t_ast **tree)
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
					return (0);
			}
		}
	}
	else if ((*tree)->rigth == NULL && (*lexer)->number > (*tree)->node)
	{
		(*tree)->rigth = create_treenode(lexer, tree, command);
		return (0);
	}
	else if ((*tree)->rigth != NULL)
		*tree = (*tree)->rigth;
	return (0);
}

void	finish_parse(t_lexer **lexer, t_ast **tree)
{
	while ((*tree)->prev != NULL)
		*tree = (*tree)->prev;
	while ((*lexer)->prev != NULL)
		*lexer = (*lexer)->prev;
}

int	second_loop(t_lexer **l, t_ast **t)
{
	while (*l)
	{
		if ((*l)->number != (*t)->node && \
		(*l)->type != pipem && is_file((*t)->type))
		{
			if (when_file(l, t))
				return (2);
		}
		else if ((*l)->number != (*t)->node && (*t)->type == pipem)
			when_pipe(l, t);
		else if ((*l)->next != NULL)
			*l = (*l)->next;
		else if ((*l)->next == NULL)
			break ;
	}
	return (0);
}

int	parsing_str(t_lexer **l, t_ast **t)
{
	first_objects(l, t);
	if (*t == NULL)
		*t = create_treenode(l, NULL, command);
	else
	{
		if ((is_file((*l)->type)) && (*l)->next == NULL)
			return (error_syntax("'newline'", 2));
		while ((*t)->prev != NULL)
			*t = (*t)->prev;
		if (second_loop(l, t))
			return (2);
	}
	finish_parse(l, t);
	return (0);
}
