/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:35:44 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/08 11:34:35 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_process(char *str, t_ast *node, int error)
{
	write(2, "minishell: ", 11);
	if (node->prev && (node->prev->type == red_in || node->prev->type == red_out))
		write(2, node->file, ft_strlen(node->file));
	else if (node && node->type == command)
		 write(2, node->command[0], ft_strlen(node->command[0]));
	write(2, " : ", 1);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	if (node->prev && (node->prev->type == red_in || node->prev->type == red_out))
		return (error);
	else if (node && node->type == command)
		exit(error);
	return (error);
}

int	error_syntax(char *str, int error)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error near unexpected token ", 35);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (error);
}

t_ast	*free_tree(t_ast *node, int a)
{
	while (node->prev != NULL && a == 0)
		node = node->prev;
	if (node->type == command)
		free_str_split(node->command);
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

void close_fd(t_ast *tree, int *pipes)
{
	int num_pipes;
	int	i;

	while (tree->prev)
		tree = tree->prev;
	num_pipes = counting_pipes(tree);
	i = 0;
	while (i < num_pipes * 2)
	{
		close(pipes[i]);
		i++;
	}
}

void	free_str_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
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