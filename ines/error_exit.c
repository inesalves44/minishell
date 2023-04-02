/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:35:44 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/02 20:44:59 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_process(char *str, t_ast *node, int error)
{
	write(2, "minishell: ", 11);
	if (node && (node->type == red_in || node->type == red_out))
		write(2, node->file, ft_strlen(node->file));
	else if (node && node->type == command)
		 write(2, node->command[0], ft_strlen(node->command[0]));
	write(2, ":", 1);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (error);
}

void	free_tree(t_ast *node, int a)
{
	int	i;

	i = 0;
	while (node->prev && a == 0)
		node = node->prev;
	if (node->type == command)
		free_str_split(node->command);
	if (node->prev)
		node->prev = NULL;
	if (node->rigth)
		free_tree(node->rigth, 1);
	if (node->left)
		free_tree(node->left, 1);
	node->rigth = NULL;
	node->left = NULL;
	free(node);
}

void close_fd(t_ast *tree, int *pipes)
{
	int num_pipes;
	int	i;

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