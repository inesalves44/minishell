/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 11:20:35 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/24 20:14:39 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast	*free_tree(t_ast *node, int a)
{
	while (node->prev != NULL && a == 0)
		node = node->prev;
	if (node->type == command && node->command != NULL)
		free_str_split(node->command);
	else if (node->type == file)
		free(node->file);
	if (node->type == command || node->type == file)
	{
		free(node->dquotes);
		free(node->squotes);
	}
	if (node->prev != NULL)
		node->prev = NULL;
	if (node->rigth != NULL)
		free_tree((node->rigth), 1);
	if (node->left != NULL)
		free_tree((node->left), 1);
	node->rigth = NULL;
	node->left = NULL;
	free(node);
	node = NULL;
	return (NULL);
}

t_lexer	*free_lexer(t_lexer *lexer)
{
	if (lexer->next != NULL)
	{
		while (lexer)
		{
			if (lexer->prev)
				lexer->prev = NULL;
			if (lexer->str)
			{
				free(lexer->str);
				lexer->str = NULL;
			}
			if (!lexer->next)
				break ;
			lexer = lexer->next;
			free(lexer->prev);
		}
		if (lexer->prev)
			lexer->prev = NULL;
		free (lexer);
	}
	else
		free(lexer);
	lexer = NULL;
	return (lexer);
}
