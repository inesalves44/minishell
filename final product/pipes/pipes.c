/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:25:07 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/28 18:48:05 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_pipes(t_root *r, int i)
{
	if (!checking_redirects_pipes(r, i, r->num_pipes + 1))
	{
		if (i != r->num_pipes)
			r->tree = r->tree->left;
		if (r->tree->type == pipem)
			r->tree = r->tree->rigth;
		if (r->tree->command && r->tree->command[0] != NULL && is_built(r->tree->command, 1))
		{
			if ((r->out == r->pipes[2 * i + 1] && i > 0) || \
			(r->out == r->pipes[1] && i == 0))
			{
				r->isbuilt = \
				open(".temp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
				r->out = r->isbuilt;
			}
			built_in_router(r);
		}
		else if (r->tree->command && r->tree->command[0] != NULL && !is_built(r->tree->command, 0))
			if (fork() == 0)
				child_in(r);
	}
	r->tree = r->tree->prev;
	if (r->tree->rigth)
		r->tree = r->tree->rigth;
}

void	final_pipe(t_root *r, pid_t *pid, int i)
{
	r->in = 0;
	r->out = 1;
	if (!checking_redirects_pipes(r, i, r->num_pipes + 1))
	{
		if (r->tree->command[0] != NULL && is_built(r->tree->command, 1))
			built_in_router(r);
		else if (r->tree->command[0] != NULL && !is_built(r->tree->command, 0))
		{
			*pid = fork();
			if (*pid == 0)
				child_out(r);
		}	
	}
}

void	init_varpipes(t_root *root, int *i, pid_t *pid)
{
	*i = 0;
	root->num_pipes = counting_pipes(root->tree);
	root->pipes = creating_pipes(root->tree, root->num_pipes);
	root->isbuilt = 0;
	*pid = 0;
}

int	doing_pipes(t_root *root)
{
	int		status;
	int		i;
	pid_t	pid;

	root->tree = checking_unfinishpipes(root->tree);
	if (root->tree == NULL)
		return (130);
	init_varpipes(root, &i, &pid);
	while (i < root->num_pipes)
	{
		root->in = 0;
		root->out = 1;
		first_pipes(root, i);
		i++;
	}
	final_pipe(root, &pid, i);
	close_fd(root->tree, root->pipes);
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_int2);
	waitpid(pid, &status, 0);
	while (i-- >= 0)
	{
		signal(SIGQUIT, sig_quit);
		signal(SIGINT, sig_int2);
		waitpid(0, NULL, 0);
	}
	deleting_tempfiles(root->tree);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
