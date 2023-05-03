/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:02:57 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/03 11:09:59 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	checking_next_node(t_ast **tree)
{
	while ((*tree)->prev)
		*tree = (*tree)->prev;
	while ((*tree)->rigth && is_file((*tree)->type))
		(*tree) = (*tree)->rigth;
}

int	simple_commands(t_root *r, int *status)
{
	pid_t	pid;

	if (checking_redirects(r, status))
		return (*status);
	checking_next_node(&r->tree);
	if (r->tree->type != command || r->tree->command[0] == NULL)
		return (0);
	if (r->tree && r->tree->type == command && !is_built(r->tree->command, 0))
	{
		pid = fork();
		if (pid == 0)
			do_command(r);
		signal(SIGINT, sig_int2);
		signal(SIGQUIT, sig_quit);
		waitpid(pid, status, 0);
	}
	else if (r->tree && r->tree->type == command && \
	is_built(r->tree->command, 0))
		*status = built_in_router(r);
	return (0);
}

void	ending_cleaning(t_ast **tree)
{
	while ((*tree)->prev)
		*tree = (*tree)->prev;
	while (*tree)
	{
		if ((*tree)->type == here_doc)
		{
			unlink(".here_doc");
			break ;
		}
		if (!(*tree)->rigth)
			break ;
		*tree = (*tree)->rigth;
	}
	if ((*tree)->prev)
		while ((*tree)->prev)
			*tree = (*tree)->prev;
}

int	checking_processes(t_root *root)
{
	int		status;
	t_ast	*aux;

	status = 0;
	aux = root->tree;
	if (check_expander(root, &aux))
		return (root->status);
	while (aux->prev)
		aux = aux->prev;
	root->tree = aux;
	if (!counting_pipes(root->tree))
	{
		simple_commands(root, &status);
		while (root->tree->prev)
			root->tree = root->tree->prev;
		ending_cleaning(&(root->tree));
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	else
	{
		status = doing_pipes(root);
		return (status);
	}
	return (status);
}
