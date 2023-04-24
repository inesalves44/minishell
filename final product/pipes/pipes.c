/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:25:07 by idias-al          #+#    #+#             */
/*   Updated: 2023/04/24 11:22:10 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checking_redirects_pipes(t_root *root, int i, int max)
{
	int	in2;
	int	out2;

	in2 = 0;
	out2 = 0;
	if (checking_redirects(root, &(root->status)))
		return (root->status);
	if (root->in == 0)
	{
		if (i == 0)
			in2 = 0;
		else if (i == max - 1)
			in2 = root->pipes[root->num_pipes * 2 - 2];
		else
			in2 = root->pipes[2 * i - 2];
		root->in = in2;
	}
	if (root->isbuilt != 0)
	{
		close(root->isbuilt);
		root->in = open(".temp", O_RDONLY);
		root->isbuilt = 0;
	}
	if (root->out == 1)
	{
		if (i == 0)
			out2 = root->pipes[1];
		else if (i == max -1)
			out2 = 1;
		else
			out2 = root->pipes[2 * i + 1];
		root->out = out2;	
	}
	return (0);
}

char	*create_completepipe(t_ast *tree)
{
	char	*str;
	char	*new;
	int		i;

	i = 0;
	str = NULL;
	new = NULL;
	while (1)
	{
		if (tree->type == pipem)
		{
			if (!tree->rigth)
			{
				while (1)
				{
					write(1, ">", 1);
					str = get_next_line(0);
					if (!str)
						return (NULL);
					while (str[i] == ' ')
						i++;
					if (str[i] != '\n')
						break ;				
				}
				break ;
			}
		}
		if (!tree->rigth)
		{
			while (tree->prev)
				tree = tree->prev;
			return (NULL);
		}
		tree = tree->rigth;
	}
	new = ft_substr(str, 0, ft_strlen(str) - 1);
	free(str);
	return (new);
}

t_ast	*checking_unfinishpipes(t_ast *tree)
{
	char	*new;
	t_lexer	*node;
	t_ast	*aux;

	aux = NULL;
	new = create_completepipe(tree);
	if (!new)
		return (tree);
	lexical_annalysis(&node, new);
	parsing_str(&node, &aux);
	tree->rigth = aux;
	aux->prev = tree;
	while (tree->prev)
		tree = tree->prev;
	free(new);
	return (tree);
}

int	doing_pipes(t_root *root)
{
	int 	status;
	int		i;
	pid_t	pid;

	root->tree = checking_unfinishpipes(root->tree);
	if (root->tree == NULL)
		return (130);
	i = 0;
	root->num_pipes = counting_pipes(root->tree);
	root->pipes = creating_pipes(root->tree, root->num_pipes);
	root->isbuilt = 0;
	pid = 0;
	while (i < root->num_pipes)
	{
		root->in = 0;
		root->out = 1;
		if (!checking_redirects_pipes(root, i, root->num_pipes + 1))
		{
			if (i != root->num_pipes)
				root->tree = root->tree->left;
			if (root->tree->type == pipem)
				root->tree = root->tree->rigth;
			if (root->tree->command[0] != NULL && is_built(root->tree->command, 1))
			{
				if ((root->out == root->pipes[2 * i + 1] && i > 0) || (root->out == root->pipes[1] && i == 0))
				{
					root->isbuilt = open(".temp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
					root->out = root->isbuilt;	
				}
				built_in_router(root);
			}
			else if (root->tree->command[0] != NULL && !is_built(root->tree->command, 0))
				if (fork() == 0)
					child_in(root);
		}
		root->tree = root->tree->prev;
		if (root->tree->rigth)
			root->tree = root->tree->rigth;
		i++;
	}
	root->in = 0;
	root->out = 1;
	if (!checking_redirects_pipes(root, i, root->num_pipes + 1))
	{
		if (root->tree->command[0] != NULL && is_built(root->tree->command, 1))
			built_in_router(root);
		else if (root->tree->command[0] != NULL && !is_built(root->tree->command, 0))
		{
			pid = fork();
			if (pid == 0)
				child_out(root);
		}	
	}
	close_fd(root->tree, root->pipes);
	waitpid(pid, &status, 0);
	while (i-- >= 0)
	{
		signal(SIGINT, sig_int2);
		waitpid(0, NULL, 0);
	}
	while (root->tree->prev)
		root->tree = root->tree->prev;
	while (root->tree)
	{
		if (root->tree->type == here_doc)
			unlink(".here_doc");
		if (root->tree->type == command && is_built(root->tree->command, 0))
			unlink(".temp");
		else if (root->tree->left && root->tree->left->type == command && is_built(root->tree->left->command, 0))
			unlink(".temp");
		if (!root->tree->rigth)
			break ;
		root->tree = root->tree->rigth;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}