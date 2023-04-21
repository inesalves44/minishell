/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:02:57 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/21 16:30:28 by hmaciel-         ###   ########.fr       */
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

int	check_expander(t_root *r, t_ast **tree)
{
	char	*value;
	int		i;

	value = NULL;
	if ((*tree)->type == file)
	{
		if ((*tree)->prev->type != here_doc && (*tree)->file[0] == '$' && (*tree)->squotes[0] == -1)
		{
			value = get_env_value(r, (*tree)->file + 1);
			free((*tree)->file);
			(*tree)->file = NULL;
			(*tree)->file = ft_strdup(value);
			free(value);
		}
	}
	else if ((*tree)->type == command)
	{
		i = 0;
		while ((*tree)->command[i])
		{
			if (!ft_strncmp("$", (*tree)->command[i], 1) && (*tree)->squotes[i] == -1)
			{
				value = get_env_value(r, (*tree)->command[i] + 1);
				if (is_equal((*tree)->command[i] + 1, "?"))
				{
					free((*tree)->command[i]);
					(*tree)->command[i] = NULL;
					(*tree)->command[i] = ft_strdup(ft_itoa(r->status_old));
				}
				else if (value)
				{
					free((*tree)->command[i]);
					(*tree)->command[i] = NULL;
					(*tree)->command[i] = ft_strdup(value);
					free(value);
				}
			}
			i++;	
		}
	}
	if ((*tree)->left)
		check_expander(r, &(*tree)->left);
	if ((*tree)->rigth)
		check_expander(r, &(*tree)->rigth);
	return(0);
}

int	checking_processes(t_root *root)
{
	pid_t	pid;
	int		status;
	t_ast	*aux;

	status = 0;
	aux = root->tree;
	check_expander(root, &aux);
	while (aux->prev)
		aux = aux->prev;
	root->tree = aux;
	if (!counting_pipes(root->tree))
	{
		if (checking_redirects(root, &status))
			return (status);
		checking_next_node(&root->tree);
		if (root->tree->type != command || root->tree->command[0] == NULL)
			return (0);
		if (root->tree && root->tree->type == command && !is_built(root->tree->command, 0))
		{
			pid = fork();
			if (pid == 0)
				do_command(root);
			signal(SIGINT, sig_int2);
			waitpid(pid, &status, 0);
		}
		else if (root->tree && root->tree->type == command && is_built(root->tree->command, 0))
			built_in_router(root);
		while (root->tree->prev)
			root->tree = root->tree->prev;
		while (root->tree)
		{
			if (root->tree->type == here_doc)
			{
				unlink(".here_doc");
				break ;
			}
			if (!root->tree->rigth)
				break ;
			root->tree = root->tree->rigth;
		}
		if (root->tree->prev)
			while (root->tree->prev)
				root->tree = root->tree->prev;
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