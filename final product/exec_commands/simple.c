/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:02:57 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/12 00:32:02 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	input_file(t_root *root)
{
	char	*buf;

	if (root->tree->type == red_in)
		root->in = open(root->tree->left->file, O_RDONLY);
	else
		root->in = open(".here_doc", O_CREAT | O_WRONLY | O_APPEND, 0000644);
	if (root->in < 0)
		return (error_process(": no such file or directory", root->tree->left, 1));
	if (root->tree->type == here_doc)
	{
		while (1)
		{
			write(1, ">", 1);
			buf = get_next_line(0);
			write(root->in, buf, ft_strlen(buf));
			if (ft_strlen(buf) == (ft_strlen(root->tree->left->file) + 1) && \
				!ft_strncmp(buf, root->tree->left->file, ft_strlen(root->tree->left->file)))
				break ;
			free(buf);
		}
		root->in = open(".here_doc", O_RDONLY);
		if (root->in < 0)
			return (error_process(": no such file or directory", root->tree->left, 1));
	}
	return (0);
}

int	output_file(t_root *root)
{
	if (root->tree->type == red_out)
		root->out = open(root->tree->left->file, O_CREAT | O_TRUNC | O_RDWR, 0000666);
	else
		root->out = open(root->tree->left->file, O_APPEND | O_CREAT | O_RDWR, 0000666);
	if (root->out < 0)
		return (error_process(": no such file or directory", root->tree->left, 1));
	return (0);
}

void	checking_next_node(t_ast **tree)
{
	while ((*tree)->prev)
		*tree = (*tree)->prev;
	while (*tree && ((*tree)->type == red_in || (*tree)->type == red_out || (*tree)->type == app_out || (*tree)->type == here_doc))
		(*tree) = (*tree)->rigth;
}

int	checking_processes(t_root *root)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!counting_pipes(root->tree))
	{
		while (root->tree)
		{
			if (root->tree->type == red_in || root->tree->type == here_doc)
				status = input_file(root);
			else if (root->tree->type == red_out || root->tree->type == app_out)
				status = output_file(root);
			if (!root->tree->rigth)
				break ;
			if (status)
				return (status);
			root->tree = root->tree->rigth;
		}
		checking_next_node(&root->tree);		
		if (root->tree && root->tree->type == command && !is_built(root->tree->command))
		{
			pid = fork();
			if (pid == 0)
				do_command(root);
			waitpid(pid, &status, 0);
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
		else if (root->tree && root->tree->type == command && is_built(root->tree->command))
			built_in_router(root);
	}
	else
	{
		status = doing_pipes(root);
		return (status);
	}
	return (status);
}